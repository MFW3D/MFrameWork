#ifndef DOT_SCENELOADER_H
#define DOT_SCENELOADER_H
//
//
//DotSceneLoader* pDotSceneLoader = new DotSceneLoader();
//pDotSceneLoader->parseDotScene("CubeScene.xml", "General", Engine3D_SceneMgr::GetInstance()->m_pSceneMgr,
//	Engine3D_SceneMgr::GetInstance()->m_pSceneMgr->getRootSceneNode());
//delete pDotSceneLoader;



// Includes
#include <OgreString.h>
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <OgreColourValue.h>
#include <OgreResourceGroupManager.h>
#include <vector>

#include "rapidxml.hpp"

    // Forward declarations
    namespace Ogre
    {
        class SceneManager;
        class SceneNode;
        class TerrainGroup;
        class TerrainGlobalOptions;
    }

    class DotSceneLoader
    {
    public:
        Ogre::TerrainGlobalOptions *mTerrainGlobalOptions;
        
        DotSceneLoader();
        virtual ~DotSceneLoader();

        void parseDotScene(const Ogre::String &SceneName, const Ogre::String &groupName, Ogre::SceneManager *yourSceneMgr, Ogre::SceneNode *pAttachNode = NULL, const Ogre::String &sPrependNode = "");

        Ogre::TerrainGroup* getTerrainGroup() { return mTerrainGroup; }

        const Ogre::ColourValue& getBackgroundColour() {
            return mBackgroundColour;
        }

        std::vector<Ogre::String> staticObjects;
        std::vector<Ogre::String> dynamicObjects;
    protected:
        void processScene(rapidxml::xml_node<>* XMLRoot);

        void processNodes(rapidxml::xml_node<>* XMLNode);
        void processExternals(rapidxml::xml_node<>* XMLNode);
        void processEnvironment(rapidxml::xml_node<>* XMLNode);
        void processTerrain(rapidxml::xml_node<>* XMLNode);
        void processTerrainPage(rapidxml::xml_node<>* XMLNode);
        void processBlendmaps(rapidxml::xml_node<>* XMLNode);
        void processUserData(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pNode);
        void processUserData(rapidxml::xml_node<>* XMLNode, Ogre::MovableObject *pMObject);
        void processLight(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent = 0);
        void processCamera(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent = 0);

        void processNode(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent = 0);
        void processLookTarget(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent);
        void processTrackTarget(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent);
        void processEntity(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent);
        void processParticleSystem(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent);
        void processBillboardSet(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent);
        void processPlane(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent);

        void processFog(rapidxml::xml_node<>* XMLNode);
        void processSkyBox(rapidxml::xml_node<>* XMLNode);
        void processSkyDome(rapidxml::xml_node<>* XMLNode);
        void processSkyPlane(rapidxml::xml_node<>* XMLNode);
        void processClipping(rapidxml::xml_node<>* XMLNode);

        void processLightRange(rapidxml::xml_node<>* XMLNode, Ogre::Light *pLight);
        void processLightAttenuation(rapidxml::xml_node<>* XMLNode, Ogre::Light *pLight);

        Ogre::SceneManager *mSceneMgr;
        Ogre::SceneNode *mAttachNode;
        Ogre::String m_sGroupName;
        Ogre::String m_sPrependNode;
        Ogre::TerrainGroup* mTerrainGroup;
        Ogre::Vector3 mTerrainPosition;
        Ogre::ColourValue mBackgroundColour;
    };

#endif // DOT_SCENELOADER_H
