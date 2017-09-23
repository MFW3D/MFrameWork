#include "MFW3D_MgrContext.h"

#include "OgreRoot.h"
#include "OgreGpuProgramManager.h"
#include "OgreConfigFile.h"
#include "OgreRenderWindow.h"
#include "OgreViewport.h"
#include "OgreOverlaySystem.h"
#include "OgreDataStream.h"
#include "OgreConfigDialog.h"
#include "MFW3D_InputMgr.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
#include "OgreArchiveManager.h"
#include "Android/OgreAPKFileSystemArchive.h"
#include "Android/OgreAPKZipArchive.h"
#endif

namespace MFW3D {

	static const char* SHADER_CACHE_FILENAME = "cache.bin";

	MFW3D_MgrContext::MFW3D_MgrContext(const Ogre::String& appName, bool grabInput)
#if (OGRE_THREAD_PROVIDER == 3) && (OGRE_NO_TBB_SCHEDULER == 1)
		: mTaskScheduler(tbb::task_scheduler_init::deferred)
#endif
	{
		mAppName = appName;
		mGrabInput = grabInput;
		mFSLayer = new Ogre::FileSystemLayer(mAppName);
		mRoot = NULL;
		mWindow = NULL;
		mOverlaySystem = NULL;
		mFirstRun = true;

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
		mAAssetMgr = NULL;
		mAConfig = NULL;
		mAWindow = NULL;
#endif

#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
		mMaterialMgrListener = NULL;
		mShaderGenerator = NULL;
#endif
	}

	MFW3D_MgrContext::~MFW3D_MgrContext()
	{
		delete mFSLayer;
	}

	void MFW3D_MgrContext::initApp()
	{
		setlocale(LC_ALL, "Chinese-simplified");
		createRoot();
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
		if (!oneTimeConfig()) return;

		if (!mFirstRun) mRoot->setRenderSystem(mRoot->getRenderSystemByName(mNextRenderer));

		setup();

		mRoot->saveConfig();

		Ogre::Root::getSingleton().getRenderSystem()->_initRenderTargets();

		// Clear event times
		Ogre::Root::getSingleton().clearEventTimes();
#else

#if OGRE_PLATFORM == OGRE_PLATFORM_NACL
		mNextRenderer = mRoot->getAvailableRenderers()[0]->getName();
#else


#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID || OGRE_PLATFORM == OGRE_PLATFORM_EMSCRIPTEN
		mRoot->setRenderSystem(mRoot->getAvailableRenderers().at(0));
#else
		if (!mRoot->restoreConfig()) {
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX || OGRE_PLATFORM == OGRE_PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_APPLE
			static Ogre::ConfigDialog dialog;
			mRoot->showConfigDialog(&dialog);
#else
			mRoot->showConfigDialog(NULL);
#endif
		}
#endif
#endif

#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID
		// if the context was reconfigured, set requested renderer
		if (!mFirstRun) mRoot->setRenderSystem(mRoot->getRenderSystemByName(mNextRenderer));
#endif
#endif
	}

	void MFW3D_MgrContext::closeApp()
	{
#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID
		mRoot->saveConfig();
#endif
		shutdown();
		if (mRoot)
		{
			OGRE_DELETE mRoot;
			mRoot = NULL;
		}
#if (OGRE_THREAD_PROVIDER == 3) && (OGRE_NO_TBB_SCHEDULER == 1)
		if (mTaskScheduler.is_active())
			mTaskScheduler.terminate();
#endif
	}

	bool MFW3D_MgrContext::initialiseRTShaderSystem()
	{
#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
		if (Ogre::RTShader::ShaderGenerator::initialize())
		{
			mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

#if OGRE_PLATFORM != OGRE_PLATFORM_NACL && OGRE_PLATFORM != OGRE_PLATFORM_WINRT
			// Core shader libs not found -> shader generating will fail.
			if (mRTShaderLibPath.empty())
				return false;
#endif

			// Create and register the material manager listener if it doesn't exist yet.
			if (!mMaterialMgrListener) {
				mMaterialMgrListener = new MFW3D_SGTRListener(mShaderGenerator);
				Ogre::MaterialManager::getSingleton().addListener(mMaterialMgrListener);
			}
		}

		return true;
#else
		return false;
#endif
	}

	void MFW3D_MgrContext::setRTSSWriteShadersToDisk(bool write)
	{
#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
		if (!write) {
			mShaderGenerator->setShaderCachePath("");
			return;
		}

		// Set shader cache path.
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
		mShaderGenerator->setShaderCachePath(Ogre::macCachePath());
#elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE
		mShaderGenerator->setShaderCachePath(Ogre::macCachePath() + "/org.ogre3d.RTShaderCache");
#else
		mShaderGenerator->setShaderCachePath(mRTShaderLibPath + "/cache/");
#endif
#endif
	}

	void MFW3D_MgrContext::destroyRTShaderSystem()
	{
#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
		//mShaderGenerator->removeAllShaderBasedTechniques();
		//mShaderGenerator->flushShaderCache();

		// Restore default scheme.
		Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

		// Unregister the material manager listener.
		if (mMaterialMgrListener != NULL)
		{
			Ogre::MaterialManager::getSingleton().removeListener(mMaterialMgrListener);
			delete mMaterialMgrListener;
			mMaterialMgrListener = NULL;
		}

		// Destroy RTShader system.
		if (mShaderGenerator != NULL)
		{
			Ogre::RTShader::ShaderGenerator::destroy();
			mShaderGenerator = NULL;
		}
#endif
	}

	void MFW3D_MgrContext::setup()
	{
		locateResources();
#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
		initialiseRTShaderSystem();
#endif
		loadResources();
		mRoot->addFrameListener(this);
#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID
		Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
#endif
	}

	void MFW3D_MgrContext::createRoot()
	{
#if (OGRE_THREAD_PROVIDER == 3) && (OGRE_NO_TBB_SCHEDULER == 1)
		mTaskScheduler.initialize(OGRE_THREAD_HARDWARE_CONCURRENCY);
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID || OGRE_PLATFORM == OGRE_PLATFORM_EMSCRIPTEN
		mRoot = OGRE_NEW Ogre::Root("");
#else
		Ogre::String pluginsPath = Ogre::BLANKSTRING;
		pluginsPath = mFSLayer->getConfigFilePath("plugins.cfg");
		mRoot = OGRE_NEW Ogre::Root(pluginsPath, mFSLayer->getWritablePath("ogre.cfg"),
			mFSLayer->getWritablePath("ogre.log"));
#endif
		mOverlaySystem = OGRE_NEW Ogre::OverlaySystem();
	}


	void MFW3D_MgrContext::createDummyScene()
	{
		mWindow->removeAllViewports();
		Ogre::SceneManager* sm = mRoot->createSceneManager(Ogre::ST_GENERIC, "DummyScene");
		sm->addRenderQueueListener(mOverlaySystem);
		Ogre::Camera* cam = sm->createCamera("DummyCamera");
		mWindow->addViewport(cam);
#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
		// Initialize shader generator.
		// Must be before resource loading in order to allow parsing extended material attributes.
		if (!initialiseRTShaderSystem())
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND,
				"Shader Generator Initialization failed - Core shader libs path not found",
				"ApplicationContext::createDummyScene");
		}

		mShaderGenerator->addSceneManager(sm);
#endif // OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
	}

	void MFW3D_MgrContext::destroyDummyScene()
	{
		if (!mRoot->hasSceneManager("DummyScene"))
			return;

		Ogre::SceneManager*  dummyScene = mRoot->getSceneManager("DummyScene");
#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
		mShaderGenerator->removeSceneManager(dummyScene);
#endif
		dummyScene->removeRenderQueueListener(mOverlaySystem);
		mWindow->removeAllViewports();
		mRoot->destroySceneManager(dummyScene);
	}

	void MFW3D_MgrContext::enableShaderCache() const
	{
		Ogre::GpuProgramManager::getSingleton().setSaveMicrocodesToCache(true);

		// Load for a package version of the shaders.
		Ogre::String path = mFSLayer->getWritablePath(SHADER_CACHE_FILENAME);
		std::fstream inFile(path.c_str(), std::ios::binary);
		if (inFile.is_open())
		{
			Ogre::LogManager::getSingleton().logMessage("Loading shader cache from " + path);
			Ogre::DataStreamPtr istream(new Ogre::FileStreamDataStream(path, &inFile, false));
			Ogre::GpuProgramManager::getSingleton().loadMicrocodeCache(istream);
		}
	}

	bool MFW3D_MgrContext::frameRenderingQueued(const Ogre::FrameEvent& evt)
	{
		return true;
	}
	//使用内部创建窗体
	Ogre::RenderWindow *MFW3D_MgrContext::createWindow()
	{
		mRoot->initialise(false, mAppName);
		Ogre::NameValuePairList miscParams;
#if OGRE_PLATFORM == OGRE_PLATFORM_NACL
		miscParams["pp::Instance"] = Ogre::StringConverter::toString((unsigned long)mNaClInstance);
		miscParams["SwapCallback"] = Ogre::StringConverter::toString((unsigned long)mNaClSwapCallback);
		// create 1x1 window - we will resize later
		return mRoot->createRenderWindow(mAppName, mInitWidth, mInitHeight, false, &miscParams);

#elif OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
		miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(reinterpret_cast<size_t>(mAWindow));
		miscParams["androidConfig"] = Ogre::StringConverter::toString(reinterpret_cast<size_t>(mAConfig));
		miscParams["preserveContext"] = "true"; //Optionally preserve the gl context, prevents reloading all resources, this is false by default

		return Ogre::Root::getSingleton().createRenderWindow(mAppName, 0, 0, false, &miscParams);
#else
		Ogre::ConfigOptionMap ropts = mRoot->getRenderSystem()->getConfigOptions();
		Ogre::uint32 w, h;
		std::istringstream mode(ropts["Video Mode"].currentValue);
		Ogre::String token;
		mode >> w; // width
		mode >> token; // 'x' as seperator between width and height
		mode >> h; // height

		miscParams["FSAA"] = ropts["FSAA"].currentValue;
		miscParams["vsync"] = ropts["VSync"].currentValue;
		SDL_SysWMinfo mWindowInfo = MFW3D_InputMgr::GetInstance()->InitWindow(mAppName, mRoot);
		miscParams["externalWindowHandle"] = Ogre::StringConverter::toString((int)mWindowInfo.info.dummy);
		mWindow = mRoot->createRenderWindow(mAppName, w, h, false, &miscParams);
		MFW3D_InputMgr::GetInstance()->init(mRoot,mWindow, std::bind(&MFW3D_MgrContext::windowResized, this, std::placeholders::_1));

		MFW3D_InputMgr::GetInstance()->SetupWindow(false);
		return mWindow;
#endif
	}
	//使用外部窗体
	Ogre::RenderWindow * MFW3D_MgrContext::createWindow(HWND m_hWnd, int width, int height)
	{
		mRoot->initialise(false, mAppName);//禁止ogre创建新的渲染窗口，而使用MFC的窗口
		Ogre::NameValuePairList miscParams;
		Ogre::ConfigOptionMap ropts = mRoot->getRenderSystem()->getConfigOptions();
		miscParams["FSAA"] = ropts["FSAA"].currentValue;
		miscParams["vsync"] = ropts["VSync"].currentValue;
		miscParams["externalWindowHandle"] = Ogre::StringConverter::toString((int)m_hWnd);
		mWindow = mRoot->createRenderWindow("OgreRenderWindow", width, height, false, &miscParams);
		MFW3D_InputMgr::GetInstance()->init(mRoot, mWindow, std::bind(&MFW3D_MgrContext::windowResized, this, std::placeholders::_1));
		return mWindow;
	}

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
	void ApplicationContext::initAppForAndroid(AAssetManager* assetMgr, ANativeWindow* window)
	{
		mAConfig = AConfiguration_new();
		AConfiguration_fromAssetManager(mAConfig, assetMgr);
		mAAssetMgr = assetMgr;
		mAWindow = window;

		initApp();
	}

	Ogre::DataStreamPtr ApplicationContext::openAPKFile(const Ogre::String& fileName)
	{
		Ogre::MemoryDataStreamPtr stream;
		AAsset* asset = AAssetManager_open(mAAssetMgr, fileName.c_str(), AASSET_MODE_BUFFER);
		if (asset)
		{
			off_t length = AAsset_getLength(asset);
			stream.reset(new Ogre::MemoryDataStream(length, true, true));
			memcpy(stream->getPtr(), AAsset_getBuffer(asset), length);
			AAsset_close(asset);
		}
		return stream;
	}

	void ApplicationContext::_fireInputEventAndroid(AInputEvent* event, int wheel) {
		Event evt = { 0 };

		static TouchFingerEvent lastTouch = { 0 };

		if (wheel) {
			evt.type = SDL_MOUSEWHEEL;
			evt.wheel.y = wheel;
			_fireInputEvent(evt);
			lastTouch.fingerId = -1; // prevent move-jump after pinch is over
			return;
		}

		if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
			int32_t action = AMOTION_EVENT_ACTION_MASK & AMotionEvent_getAction(event);

			switch (action) {
			case AMOTION_EVENT_ACTION_DOWN:
				evt.type = SDL_FINGERDOWN;
				break;
			case AMOTION_EVENT_ACTION_UP:
				evt.type = SDL_FINGERUP;
				break;
			case AMOTION_EVENT_ACTION_MOVE:
				evt.type = SDL_FINGERMOTION;
				break;
			default:
				return;
			}

			evt.tfinger.fingerId = AMotionEvent_getPointerId(event, 0);
			evt.tfinger.x = AMotionEvent_getRawX(event, 0) / mWindow->getWidth();
			evt.tfinger.y = AMotionEvent_getRawY(event, 0) / mWindow->getHeight();

			if (evt.type == SDL_FINGERMOTION) {
				if (evt.tfinger.fingerId != lastTouch.fingerId)
					return; // wrong finger

				evt.tfinger.dx = evt.tfinger.x - lastTouch.x;
				evt.tfinger.dy = evt.tfinger.y - lastTouch.y;
			}

			lastTouch = evt.tfinger;
		}
		else {
			if (AKeyEvent_getKeyCode(event) != AKEYCODE_BACK)
				return;

			evt.type = AKeyEvent_getAction(event) == AKEY_EVENT_ACTION_DOWN ? SDL_KEYDOWN : SDL_KEYUP;
			evt.key.keysym.sym = SDLK_ESCAPE;
		}

		_fireInputEvent(evt);
	}
#endif

	void MFW3D_MgrContext::locateResources()
	{
#if OGRE_PLATFORM == OGRE_PLATFORM_NACL
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Essential.zip", "EmbeddedZip", "Essential");
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Popular.zip", "EmbeddedZip", "General");
#else
		// load resource paths from config file
		Ogre::ConfigFile cf;
#   if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
		Ogre::ArchiveManager::getSingleton().addArchiveFactory(new Ogre::APKFileSystemArchiveFactory(mAAssetMgr));
		Ogre::ArchiveManager::getSingleton().addArchiveFactory(new Ogre::APKZipArchiveFactory(mAAssetMgr));
		cf.load(openAPKFile(mFSLayer->getConfigFilePath("resources.cfg")));
#   else
		cf.load(mFSLayer->getConfigFilePath("resources.cfg"));
#   endif

		Ogre::String sec, type, arch;
		// go through all specified resource groups
		Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
		for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
			sec = seci->first;
			const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
			Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

			// go through all resource paths
			for (i = settings.begin(); i != settings.end(); i++)
			{
				type = i->first;
				arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);

				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
			}
		}

		sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
		const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

		OgreAssert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

		arch = genLocs.front()->archive->getName();

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
		arch = Ogre::macBundlePath() + "/Contents/Resources/Media";
#elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
		arch = Ogre::macBundlePath() + "/Media";
#else
		arch = Ogre::StringUtil::replaceAll(arch, "Media/../../Tests/Media", "");
		arch = Ogre::StringUtil::replaceAll(arch, "media/../../Tests/Media", "");
# endif
		type = genLocs.front()->archive->getType();

#ifdef OGRE_BUILD_PLUGIN_CG
		bool use_HLSL_Cg_shared = true;
#else
		bool use_HLSL_Cg_shared = Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl");
#endif

		// Add locations for supported shader languages
		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSLES", type, sec);
		}
		else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL120", type, sec);

			if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
			{
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL150", type, sec);
			}
			else
			{
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL", type, sec);
			}

			if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl400"))
			{
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL400", type, sec);
			}
		}
		else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/HLSL", type, sec);
		}
#ifdef OGRE_BUILD_PLUGIN_CG
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/Cg", type, sec);
#endif
		if (use_HLSL_Cg_shared)
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/HLSL_Cg", type, sec);
		}

#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
		mRTShaderLibPath = arch + "/RTShaderLib";
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/materials", type, sec);

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL", type, sec);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSLES", type, sec);
		}
		else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL", type, sec);
		}
		else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/HLSL", type, sec);
		}
#   ifdef OGRE_BUILD_PLUGIN_CG
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/Cg", type, sec);
#   endif
		if (use_HLSL_Cg_shared)
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/HLSL_Cg", type, sec);
		}
#endif /* OGRE_BUILD_COMPONENT_RTSHADERSYSTEM */
#endif /* OGRE_PLATFORM == OGRE_PLATFORM_NACL */
	}

	void MFW3D_MgrContext::loadResources()
	{
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}

	void MFW3D_MgrContext::reconfigure(const Ogre::String &renderer, Ogre::NameValuePairList &options)
	{
		mNextRenderer = renderer;
		Ogre::RenderSystem* rs = mRoot->getRenderSystemByName(renderer);

		// set all given render system options
		for (Ogre::NameValuePairList::iterator it = options.begin(); it != options.end(); it++)
		{
			rs->setConfigOption(it->first, it->second);

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
			// Change the viewport orientation on the fly if requested
			if (it->first == "Orientation")
			{
				if (it->second == "Landscape Left")
					mWindow->getViewport(0)->setOrientationMode(Ogre::OR_LANDSCAPELEFT, true);
				else if (it->second == "Landscape Right")
					mWindow->getViewport(0)->setOrientationMode(Ogre::OR_LANDSCAPERIGHT, true);
				else if (it->second == "Portrait")
					mWindow->getViewport(0)->setOrientationMode(Ogre::OR_PORTRAIT, true);
			}
#endif
		}

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
		// Need to save the config on iOS to make sure that changes are kept on disk
		mRoot->saveConfig();
#endif
		mRoot->queueEndRendering();   // break from render loop
	}

	void MFW3D_MgrContext::shutdown()
	{
		if (Ogre::GpuProgramManager::getSingleton().isCacheDirty())
		{
			Ogre::String path = mFSLayer->getWritablePath(SHADER_CACHE_FILENAME);
			std::fstream outFile(path.c_str(), std::ios::out | std::ios::binary);

			if (outFile.is_open())
			{
				Ogre::LogManager::getSingleton().logMessage("Writing shader cache to " + path);
				Ogre::DataStreamPtr ostream(new Ogre::FileStreamDataStream(path, &outFile, false));
				Ogre::GpuProgramManager::getSingleton().saveMicrocodeCache(ostream);
			}
		}

#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
		// Destroy the RT Shader System.
		destroyRTShaderSystem();
#endif

		// remove window event listener before destroying it
		if (mWindow) {
			Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
			mRoot->destroyRenderTarget(mWindow);
			mWindow = NULL;
		}

		if (mOverlaySystem)
		{
			OGRE_DELETE mOverlaySystem;
		}
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
		AConfiguration_delete(mAConfig);
#endif
		MFW3D_InputMgr::GetInstance()->Destroy();
	}

	bool MFW3D_MgrContext::pollEvents()
	{
		return MFW3D_InputMgr::GetInstance()->PollEvent();
	}
}
