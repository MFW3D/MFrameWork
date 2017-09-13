#pragma once
#include "OgreBitesPrerequisites.h"
#include "OgreOverlay.h"
#include "OgreOverlaySystem.h"
#include "OgreOverlayManager.h"
#include "OgreBorderPanelOverlayElement.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"
#include "OgreTimer.h"
#include "OgreRoot.h"
#include "OgreCamera.h"
#include "OgreRenderWindow.h"
#include "MFW3D_Input.h"
#include <iomanip>
namespace MFW3D
{
	//锚点位置
    enum TrayLocation   
    {
        TL_TOPLEFT,
        TL_TOP,
        TL_TOPRIGHT,
        TL_LEFT,
        TL_CENTER,
        TL_RIGHT,
        TL_BOTTOMLEFT,
        TL_BOTTOM,
        TL_BOTTOMRIGHT,
        TL_NONE
    };
	//按钮状态
    enum ButtonState  
    {
        BS_UP,
        BS_OVER,
        BS_DOWN
    };
    class Widget;
    class Button;
    class SelectMenu;
    class Label;
    class Slider;
    class CheckBox;
	//界面事件
    class  MFW3D_UIListener
    {
    public:
        virtual ~MFW3D_UIListener() {}
        virtual void buttonHit(Button* button) {}
        virtual void itemSelected(SelectMenu* menu) {}
        virtual void labelHit(Label* label) {}
        virtual void sliderMoved(Slider* slider) {}
        virtual void checkBoxToggled(CheckBox* box) {}
        virtual void okDialogClosed(const Ogre::DisplayString& message) {}
        virtual void yesNoDialogClosed(const Ogre::DisplayString& question, bool yesHit) {}
    };
    class  Widget
    {
    public:
        Widget();
        virtual ~Widget() {}
        void cleanup();
        //递归的删除控件刻下面的所有子控件
        static void nukeOverlayElement(Ogre::OverlayElement* element);
		//检查光标是否在控件上面
        static bool isCursorOver(Ogre::OverlayElement* element, const Ogre::Vector2& cursorPos, Ogre::Real voidBorder = 0);
		//光标在控件上的位移
        static Ogre::Vector2 cursorOffset(Ogre::OverlayElement* element, const Ogre::Vector2& cursorPos);
		//获取秒数文字的宽度
        static Ogre::Real getCaptionWidth(const Ogre::DisplayString& caption, Ogre::TextAreaOverlayElement* area);
		//截取文字来适应宽度
        static void fitCaptionToArea(const Ogre::DisplayString& caption, Ogre::TextAreaOverlayElement* area, Ogre::Real maxWidth);
        Ogre::OverlayElement* getOverlayElement()
        {
            return mElement;
        }
        const Ogre::String& getName()
        {
            return mElement->getName();
        }
        TrayLocation getTrayLocation()
        {
            return mTrayLoc;
        }
        void hide()
        {
            mElement->hide();
        }
        void show()
        {
            mElement->show();
        }
        bool isVisible()
        {
            return mElement->isVisible();
        }
        virtual void _cursorPressed(const Ogre::Vector2& cursorPos) {}
        virtual void _cursorReleased(const Ogre::Vector2& cursorPos) {}
        virtual void _cursorMoved(const Ogre::Vector2& cursorPos, float wheelDelta) {}
        virtual void _focusLost() {}
		//不直接调用
		void _assignToTray(TrayLocation trayLoc) { mTrayLoc = trayLoc; }
        void _assignListener(MFW3D_UIListener* listener) { mListener = listener; }
    protected:
        Ogre::OverlayElement* mElement;
        TrayLocation mTrayLoc;
        MFW3D_UIListener* mListener;
    };
    typedef std::vector<Widget*> WidgetList;
    typedef Ogre::VectorIterator<WidgetList> WidgetIterator;
    class  Button : public Widget
    {
    public:
        //使用trayManager创建控件
        Button(const Ogre::String& name, const Ogre::DisplayString& caption, Ogre::Real width);
        virtual ~Button() {}
        const Ogre::DisplayString& getCaption()
        {
            return mTextArea->getCaption();
        }
        void setCaption(const Ogre::DisplayString& caption);
        const ButtonState& getState() { return mState; }
        void _cursorPressed(const Ogre::Vector2& cursorPos);
        void _cursorReleased(const Ogre::Vector2& cursorPos);
        void _cursorMoved(const Ogre::Vector2& cursorPos, float wheelDelta);
        void _focusLost();
    protected:
        void setState(const ButtonState& bs);
        ButtonState mState;
        Ogre::BorderPanelOverlayElement* mBP;
        Ogre::TextAreaOverlayElement* mTextArea;
        bool mFitToContents;
    };  
    class  TextBox : public Widget
    {
    public:
        TextBox(const Ogre::String& name, const Ogre::DisplayString& caption, Ogre::Real width, Ogre::Real height);
        void setPadding(Ogre::Real padding);
        Ogre::Real getPadding()
        {
            return mPadding;
        }
        const Ogre::DisplayString& getCaption()
        {
            return mCaptionTextArea->getCaption();
        }
        void setCaption(const Ogre::DisplayString& caption)
        {
            mCaptionTextArea->setCaption(caption);
        }
        const Ogre::DisplayString& getText()
        {
            return mText;
        }
        void setText(const Ogre::DisplayString& text);
        void setTextAlignment(Ogre::TextAreaOverlayElement::Alignment ta);
        void clearText()
        {
            setText("");
        }
        void appendText(const Ogre::DisplayString& text)
        {
            setText(getText() + text);
        }
        void refitContents();
        void setScrollPercentage(Ogre::Real percentage);
        Ogre::Real getScrollPercentage()
        {
            return mScrollPercentage;
        }
        unsigned int getHeightInLines()
        {
            return (unsigned int) ((mElement->getHeight() - 2 * mPadding - mCaptionBar->getHeight() + 5) / mTextArea->getCharHeight());
        }
        void _cursorPressed(const Ogre::Vector2& cursorPos);
        void _cursorReleased(const Ogre::Vector2& cursorPos)
        {
            mDragging = false;
        }
        void _cursorMoved(const Ogre::Vector2& cursorPos, float wheelDelta);
        void _focusLost()
        {
            mDragging = false;  // stop dragging if cursor was lost
        }
    protected:
        void filterLines();
        Ogre::TextAreaOverlayElement* mTextArea;
        Ogre::BorderPanelOverlayElement* mCaptionBar;
        Ogre::TextAreaOverlayElement* mCaptionTextArea;
        Ogre::BorderPanelOverlayElement* mScrollTrack;
        Ogre::PanelOverlayElement* mScrollHandle;
        Ogre::DisplayString mText;
        Ogre::StringVector mLines;
        Ogre::Real mPadding;
        bool mDragging;
        Ogre::Real mScrollPercentage;
        Ogre::Real mDragOffset;
        unsigned int mStartingLine;
    };
    class  SelectMenu : public Widget
    {
    public:
        SelectMenu(const Ogre::String& name, const Ogre::DisplayString& caption, Ogre::Real width,
            Ogre::Real boxWidth, size_t maxItemsShown);
        void copyItemsFrom(SelectMenu* other);
        bool isExpanded()
        {
            return mExpanded;
        }
        const Ogre::DisplayString& getCaption()
        {
            return mTextArea->getCaption();
        }
        void setCaption(const Ogre::DisplayString& caption);
        const Ogre::StringVector& getItems()
        {
            return mItems;
        }
        size_t getNumItems()
        {
            return mItems.size();
        }
        void setItems(const Ogre::StringVector& items);
        void addItem(const Ogre::DisplayString& item)
        {
            mItems.push_back(item);
            setItems(mItems);
        }
        void insertItem(size_t index, const Ogre::DisplayString& item)
        {
            mItems.insert(mItems.begin() + index, item);
            setItems(mItems);
        }
        void removeItem(const Ogre::DisplayString& item);
        void removeItem(size_t index);
        void clearItems();
        OGRE_DEPRECATED size_t getItemsCount()
        {
            return mItems.size();
        }
        void selectItem(size_t index, bool notifyListener = true);
        bool containsItem(const Ogre::DisplayString& item);
        void selectItem(const Ogre::DisplayString& item, bool notifyListener = true);
        Ogre::DisplayString getSelectedItem();
        int getSelectionIndex()
        {
            return mSelectionIndex;
        }
        void _cursorPressed(const Ogre::Vector2& cursorPos);
        void _cursorReleased(const Ogre::Vector2& cursorPos)
        {
            mDragging = false;
        }
        void _cursorMoved(const Ogre::Vector2& cursorPos, float wheelDelta);
        void _focusLost()
        {
            if (mExpandedBox->isVisible()) retract();
        }
    protected:
        void setDisplayIndex(unsigned int index);
        void retract();
        Ogre::BorderPanelOverlayElement* mSmallBox;
        Ogre::BorderPanelOverlayElement* mExpandedBox;
        Ogre::TextAreaOverlayElement* mTextArea;
        Ogre::TextAreaOverlayElement* mSmallTextArea;
        Ogre::BorderPanelOverlayElement* mScrollTrack;
        Ogre::PanelOverlayElement* mScrollHandle;
        std::vector<Ogre::BorderPanelOverlayElement*> mItemElements;
        size_t mMaxItemsShown;
        size_t mItemsShown;
        bool mCursorOver;
        bool mExpanded;
        bool mFitToContents;
        bool mDragging;
        Ogre::StringVector mItems;
        int mSelectionIndex;
        int mHighlightIndex;
        int mDisplayIndex;
        Ogre::Real mDragOffset;
    };
    class  Label : public Widget
    {
    public:
        Label(const Ogre::String& name, const Ogre::DisplayString& caption, Ogre::Real width);
        const Ogre::DisplayString& getCaption()
        {
            return mTextArea->getCaption();
        }
        void setCaption(const Ogre::DisplayString& caption)
        {
            mTextArea->setCaption(caption);
        }
        void _cursorPressed(const Ogre::Vector2& cursorPos);
        bool _isFitToTray()
        {
            return mFitToTray;
        }
    protected:
        Ogre::TextAreaOverlayElement* mTextArea;
        bool mFitToTray;
    };
    class  Separator : public Widget
    {
    public:
        Separator(const Ogre::String& name, Ogre::Real width);
        bool _isFitToTray()
        {
            return mFitToTray;
        }
    protected:
        bool mFitToTray;
    };
    class  Slider : public Widget
    {
    public:
        Slider(const Ogre::String& name, const Ogre::DisplayString& caption, Ogre::Real width, Ogre::Real trackWidth,
            Ogre::Real valueBoxWidth, Ogre::Real minValue, Ogre::Real maxValue, unsigned int snaps);
        void setRange(Ogre::Real minValue, Ogre::Real maxValue, unsigned int snaps, bool notifyListener = true);
        const Ogre::DisplayString& getValueCaption()
        {
            return mValueTextArea->getCaption();
        }
        void setValueCaption(const Ogre::DisplayString& caption)
        {
            mValueTextArea->setCaption(caption);
        }
        void setValue(Ogre::Real value, bool notifyListener = true);
        Ogre::Real getValue()
        {
            return mValue;
        }
        const Ogre::DisplayString& getCaption()
        {
            return mTextArea->getCaption();
        }
        void setCaption(const Ogre::DisplayString& caption);
        void _cursorPressed(const Ogre::Vector2& cursorPos);
        void _cursorReleased(const Ogre::Vector2& cursorPos);
        void _cursorMoved(const Ogre::Vector2& cursorPos, float wheelDelta);
        void _focusLost()
        {
            mDragging = false;
        }
    protected:
        Ogre::Real getSnappedValue(Ogre::Real percentage)
        {
            percentage = Ogre::Math::Clamp<Ogre::Real>(percentage, 0, 1);
            unsigned int whichMarker = (unsigned int) (percentage * (mMaxValue - mMinValue) / mInterval + 0.5);
            return whichMarker * mInterval + mMinValue;
        }
        Ogre::TextAreaOverlayElement* mTextArea;
        Ogre::TextAreaOverlayElement* mValueTextArea;
        Ogre::BorderPanelOverlayElement* mTrack;
        Ogre::PanelOverlayElement* mHandle;
        bool mDragging;
        bool mFitToContents;
        Ogre::Real mDragOffset;
        Ogre::Real mValue;
        Ogre::Real mMinValue;
        Ogre::Real mMaxValue;
        Ogre::Real mInterval;
    };
    class  ParamsPanel : public Widget
    {
    public:
        ParamsPanel(const Ogre::String& name, Ogre::Real width, unsigned int lines);
        void setAllParamNames(const Ogre::StringVector& paramNames);
        const Ogre::StringVector& getAllParamNames()
        {
            return mNames;
        }
        void setAllParamValues(const Ogre::StringVector& paramValues);
        void setParamValue(const Ogre::DisplayString& paramName, const Ogre::DisplayString& paramValue);
        void setParamValue(unsigned int index, const Ogre::DisplayString& paramValue);
        Ogre::DisplayString getParamValue(const Ogre::DisplayString& paramName);
        Ogre::DisplayString getParamValue(unsigned int index);
        const Ogre::StringVector& getAllParamValues()
        {
            return mValues;
        }
    protected:
        void updateText();
        Ogre::TextAreaOverlayElement* mNamesArea;
        Ogre::TextAreaOverlayElement* mValuesArea;
        Ogre::StringVector mNames;
        Ogre::StringVector mValues;
    };
    class  CheckBox : public Widget
    {
    public:
        CheckBox(const Ogre::String& name, const Ogre::DisplayString& caption, Ogre::Real width);
        const Ogre::DisplayString& getCaption()
        {
            return mTextArea->getCaption();
        }
        void setCaption(const Ogre::DisplayString& caption);
        bool isChecked()
        {
            return mX->isVisible();
        }
        void setChecked(bool checked, bool notifyListener = true);
        void toggle(bool notifyListener = true);
        void _cursorPressed(const Ogre::Vector2& cursorPos);
        void _cursorMoved(const Ogre::Vector2& cursorPos, float wheelDelta);
        void _focusLost();
    protected:
        Ogre::TextAreaOverlayElement* mTextArea;
        Ogre::BorderPanelOverlayElement* mSquare;
        Ogre::OverlayElement* mX;
        bool mFitToContents;
        bool mCursorOver;
    };
    class  DecorWidget : public Widget
    {
    public:
        DecorWidget(const Ogre::String& name, const Ogre::String& templateName);
    };
    class  ProgressBar : public Widget
    {
    public:
        ProgressBar(const Ogre::String& name, const Ogre::DisplayString& caption, Ogre::Real width, Ogre::Real commentBoxWidth);
        void setProgress(Ogre::Real progress);
        Ogre::Real getProgress()
        {
            return mProgress;
        }
        const Ogre::DisplayString& getCaption()
        {
            return mTextArea->getCaption();
        }
        void setCaption(const Ogre::DisplayString& caption)
        {
            mTextArea->setCaption(caption);
        }
        const Ogre::DisplayString& getComment()
        {
            return mCommentTextArea->getCaption();
        }
        void setComment(const Ogre::DisplayString& comment)
        {
            mCommentTextArea->setCaption(comment);
        }
    protected:
        Ogre::TextAreaOverlayElement* mTextArea;
        Ogre::TextAreaOverlayElement* mCommentTextArea;
        Ogre::OverlayElement* mMeter;
        Ogre::OverlayElement* mFill;
        Ogre::Real mProgress;
    };
    class  MFW3D_UIMgr : public MFW3D_UIListener, public Ogre::ResourceGroupListener, public MFW3D_InputListener
    {
    public:
		//创建trayManager
        MFW3D_UIMgr(const Ogre::String& name, Ogre::RenderWindow* window, MFW3D_UIListener* listener = 0);
        virtual ~MFW3D_UIMgr();
		//将屏幕坐标转为三维坐标
		static Ogre::Ray screenToScene(Ogre::Camera* cam, const Ogre::Vector2& pt);
		//将三维坐标转为屏幕坐标
        static Ogre::Vector2 sceneToScreen(Ogre::Camera* cam, const Ogre::Vector3& pt);
		//获取界面元素
        Ogre::OverlayContainer* getTrayContainer(TrayLocation trayLoc) { return mTrays[trayLoc]; }
        Ogre::Overlay* getBackdropLayer() { return mBackdropLayer; }
        Ogre::Overlay* getTraysLayer() { return mTraysLayer; }
        Ogre::Overlay* getCursorLayer() { return mCursorLayer; }
        Ogre::OverlayContainer* getBackdropContainer() { return mBackdrop; }
        Ogre::OverlayContainer* getCursorContainer() { return mCursor; }
        Ogre::OverlayElement* getCursorImage() { return mCursor->getChild(mCursor->getName() + "/CursorImage"); }
		//设置事件监听
        void setListener(MFW3D_UIListener* listener)
        {
            mListener = listener;
        }
        MFW3D_UIListener* getListener()
        {
            return mListener;
        }
        void showAll();
        void hideAll();
		//显示背景
        void showBackdrop(const Ogre::String& materialName = Ogre::BLANKSTRING);
        void hideBackdrop()
        {
            mBackdropLayer->hide();
        }
		//显示光标
		void showCursor(const Ogre::String& materialName = Ogre::BLANKSTRING);
        void hideCursor();
        void refreshCursor();
        void showTrays();
        void hideTrays();
        bool isCursorVisible() { return mCursorLayer->isVisible(); }
        bool isBackdropVisible() { return mBackdropLayer->isVisible(); }
        bool areTraysVisible() { return mTraysLayer->isVisible(); }
        void setTrayWidgetAlignment(TrayLocation trayLoc, Ogre::GuiHorizontalAlignment gha);
        void setWidgetPadding(Ogre::Real padding);
        void setWidgetSpacing(Ogre::Real spacing);
        void setTrayPadding(Ogre::Real padding);
        virtual Ogre::Real getWidgetPadding() const { return mWidgetPadding; }
        virtual Ogre::Real getWidgetSpacing() const { return mWidgetSpacing; }
        virtual Ogre::Real getTrayPadding() const { return mTrayPadding; }
        virtual void adjustTrays();
        Ogre::Ray getCursorRay(Ogre::Camera* cam);
        Button* createButton(TrayLocation trayLoc, const Ogre::String& name, const Ogre::String& caption, Ogre::Real width = 0);
        TextBox* createTextBox(TrayLocation trayLoc, const Ogre::String& name, const Ogre::DisplayString& caption,
            Ogre::Real width, Ogre::Real height);
        SelectMenu* createThickSelectMenu(TrayLocation trayLoc, const Ogre::String& name, const Ogre::DisplayString& caption,
            Ogre::Real width, unsigned int maxItemsShown, const Ogre::StringVector& items = Ogre::StringVector());
        SelectMenu* createLongSelectMenu(TrayLocation trayLoc, const Ogre::String& name, const Ogre::DisplayString& caption,
            Ogre::Real width, Ogre::Real boxWidth, unsigned int maxItemsShown, const Ogre::StringVector& items = Ogre::StringVector());
        SelectMenu* createLongSelectMenu(TrayLocation trayLoc, const Ogre::String& name, const Ogre::DisplayString& caption,
            Ogre::Real boxWidth, unsigned int maxItemsShown, const Ogre::StringVector& items = Ogre::StringVector());
        Label* createLabel(TrayLocation trayLoc, const Ogre::String& name, const Ogre::DisplayString& caption, Ogre::Real width = 0);
        Separator* createSeparator(TrayLocation trayLoc, const Ogre::String& name, Ogre::Real width = 0);
        Slider* createThickSlider(TrayLocation trayLoc, const Ogre::String& name, const Ogre::DisplayString& caption,
            Ogre::Real width, Ogre::Real valueBoxWidth, Ogre::Real minValue, Ogre::Real maxValue, unsigned int snaps);
        Slider* createLongSlider(TrayLocation trayLoc, const Ogre::String& name, const Ogre::DisplayString& caption, Ogre::Real width,
            Ogre::Real trackWidth, Ogre::Real valueBoxWidth, Ogre::Real minValue, Ogre::Real maxValue, unsigned int snaps);
        Slider* createLongSlider(TrayLocation trayLoc, const Ogre::String& name, const Ogre::DisplayString& caption,
            Ogre::Real trackWidth, Ogre::Real valueBoxWidth, Ogre::Real minValue, Ogre::Real maxValue, unsigned int snaps);
        ParamsPanel* createParamsPanel(TrayLocation trayLoc, const Ogre::String& name, Ogre::Real width, unsigned int lines);
        ParamsPanel* createParamsPanel(TrayLocation trayLoc, const Ogre::String& name, Ogre::Real width,
            const Ogre::StringVector& paramNames);
        CheckBox* createCheckBox(TrayLocation trayLoc, const Ogre::String& name, const Ogre::DisplayString& caption,
            Ogre::Real width = 0);
        DecorWidget* createDecorWidget(TrayLocation trayLoc, const Ogre::String& name, const Ogre::String& templateName);
        ProgressBar* createProgressBar(TrayLocation trayLoc, const Ogre::String& name, const Ogre::DisplayString& caption,
            Ogre::Real width, Ogre::Real commentBoxWidth);
        void showFrameStats(TrayLocation trayLoc, size_t place = -1);
        void hideFrameStats();
        bool areFrameStatsVisible()
        {
            return mFpsLabel != 0;
        }
        void toggleAdvancedFrameStats()
        {
            if (mFpsLabel) labelHit(mFpsLabel);
        }
        void showLogo(TrayLocation trayLoc, size_t place = -1);
        void hideLogo();
        bool isLogoVisible()
        {
            return mLogo != 0;
        }
        void showLoadingBar(unsigned int numGroupsInit = 1, unsigned int numGroupsLoad = 1,
            Ogre::Real initProportion = 0.7);
        void hideLoadingBar();
        bool isLoadingBarVisible()
        {
            return mLoadBar != 0;
        }
        void showOkDialog(const Ogre::DisplayString& caption, const Ogre::DisplayString& message);
        void showYesNoDialog(const Ogre::DisplayString& caption, const Ogre::DisplayString& question);
        void closeDialog();
        bool isDialogVisible();
        OGRE_DEPRECATED Widget* getWidget(TrayLocation trayLoc, unsigned int place);
        Widget* getWidget(TrayLocation trayLoc, const Ogre::String& name);
        Widget* getWidget(const Ogre::String& name);
        unsigned int getNumWidgets();
        OGRE_DEPRECATED size_t getNumWidgets(TrayLocation trayLoc);
        OGRE_DEPRECATED WidgetIterator getWidgetIterator(TrayLocation trayLoc);
        const WidgetList& getWidgets(TrayLocation trayLoc) const {
            return mWidgets[trayLoc];
        }
        int locateWidgetInTray(Widget* widget);
        void destroyWidget(Widget* widget);
        void destroyWidget(TrayLocation trayLoc, size_t place)
        {
            destroyWidget(mWidgets[trayLoc][place]);
        }
        void destroyWidget(TrayLocation trayLoc, const Ogre::String& name)
        {
            destroyWidget(getWidget(trayLoc, name));
        }
        void destroyWidget(const Ogre::String& name)
        {
            destroyWidget(getWidget(name));
        }
        void destroyAllWidgetsInTray(TrayLocation trayLoc);
        void destroyAllWidgets();
        void moveWidgetToTray(Widget* widget, TrayLocation trayLoc, size_t place = -1);
        void moveWidgetToTray(const Ogre::String& name, TrayLocation trayLoc, size_t place = -1)
        {
            moveWidgetToTray(getWidget(name), trayLoc, place);
        }
        void moveWidgetToTray(TrayLocation currentTrayLoc, const Ogre::String& name, TrayLocation targetTrayLoc,
            size_t place = -1)
        {
            moveWidgetToTray(getWidget(currentTrayLoc, name), targetTrayLoc, place);
        }
        void moveWidgetToTray(TrayLocation currentTrayLoc, size_t currentPlace, TrayLocation targetTrayLoc,
            size_t targetPlace = -1)
        {
            moveWidgetToTray(mWidgets[currentTrayLoc][currentPlace], targetTrayLoc, targetPlace);
        }
        void removeWidgetFromTray(Widget* widget)
        {
            moveWidgetToTray(widget, TL_NONE);
        }
        void removeWidgetFromTray(const Ogre::String& name)
        {
            removeWidgetFromTray(getWidget(name));
        }
        void removeWidgetFromTray(TrayLocation trayLoc, const Ogre::String& name)
        {
            removeWidgetFromTray(getWidget(trayLoc, name));
        }
        void removeWidgetFromTray(TrayLocation trayLoc, size_t place)
        {
            removeWidgetFromTray(mWidgets[trayLoc][place]);
        }
        void clearTray(TrayLocation trayLoc);
        void clearAllTrays();
        void frameRendered(const Ogre::FrameEvent& evt);
        void windowUpdate();
        void resourceGroupScriptingStarted(const Ogre::String& groupName, size_t scriptCount)
        {
            mLoadInc = mGroupInitProportion / scriptCount;
            mLoadBar->setCaption("Parsing...");
            windowUpdate();
        }
        void scriptParseStarted(const Ogre::String& scriptName, bool& skipThisScript)
        {
            mLoadBar->setComment(scriptName);
            windowUpdate();
        }
        void scriptParseEnded(const Ogre::String& scriptName, bool skipped)
        {
            mLoadBar->setProgress(mLoadBar->getProgress() + mLoadInc);
            windowUpdate();
        }
        void resourceGroupLoadStarted(const Ogre::String& groupName, size_t resourceCount)
        {
            mLoadInc = mGroupLoadProportion / resourceCount;
            mLoadBar->setCaption("Loading...");
            windowUpdate();
        }
        void resourceLoadStarted(const Ogre::ResourcePtr& resource)
        {
            mLoadBar->setComment(resource->getName());
            windowUpdate();
        }
        void resourceLoadEnded()
        {
            mLoadBar->setProgress(mLoadBar->getProgress() + mLoadInc);
            windowUpdate();
        }
        void worldGeometryStageStarted(const Ogre::String& description)
        {
            mLoadBar->setComment(description);
            windowUpdate();
        }
        void worldGeometryStageEnded()
        {
            mLoadBar->setProgress(mLoadBar->getProgress() + mLoadInc);
            windowUpdate();
        }
        void labelHit(Label* label);
        void buttonHit(Button* button);
        bool mousePressed(const MouseButtonEvent& evt);
        bool mouseReleased(const MouseButtonEvent& evt);
        bool mouseMoved(const MouseMotionEvent& evt);
    protected:
        void setExpandedMenu(SelectMenu* m);
        Ogre::String mName;                   // name of this tray system
        Ogre::RenderWindow* mWindow;          // render window
        Ogre::Overlay* mBackdropLayer;        // backdrop layer
        Ogre::Overlay* mTraysLayer;           // widget layer
        Ogre::Overlay* mPriorityLayer;        // top priority layer
        Ogre::Overlay* mCursorLayer;          // cursor layer
        Ogre::OverlayContainer* mBackdrop;    // backdrop
        Ogre::OverlayContainer* mTrays[10];   // widget trays
        WidgetList mWidgets[10];              // widgets
        WidgetList mWidgetDeathRow;           // widget queue for deletion
        Ogre::OverlayContainer* mCursor;      // cursor
        MFW3D_UIListener* mListener;           // tray listener
        Ogre::Real mWidgetPadding;            // widget padding
        Ogre::Real mWidgetSpacing;            // widget spacing
        Ogre::Real mTrayPadding;              // tray padding
        bool mTrayDrag;                       // a mouse press was initiated on a tray
        SelectMenu* mExpandedMenu;            // top priority expanded menu widget
        TextBox* mDialog;                     // top priority dialog widget
        Ogre::OverlayContainer* mDialogShade; // top priority dialog shade
        Button* mOk;                          // top priority OK button
        Button* mYes;                         // top priority Yes button
        Button* mNo;                          // top priority No button
        bool mCursorWasVisible;               // cursor state before showing dialog
        Label* mFpsLabel;                     // FPS label
        ParamsPanel* mStatsPanel;             // frame stats panel
        DecorWidget* mLogo;                   // logo
        ProgressBar* mLoadBar;                // loading bar
        Ogre::Real mGroupInitProportion;      // proportion of load job assigned to initialising one resource group
        Ogre::Real mGroupLoadProportion;      // proportion of load job assigned to loading one resource group
        Ogre::Real mLoadInc;                  // loading increment
        Ogre::GuiHorizontalAlignment mTrayWidgetAlign[10];   // tray widget alignments
        Ogre::Timer* mTimer;                  // Root::getSingleton().getTimer()
        unsigned long mLastStatUpdateTime;    // The last time the stat text were updated

    };
}
