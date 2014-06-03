/* Copyright (c) 2012 Research In Motion Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef FRONTEND_H
#define FRONTEND_H

#include <History/Game.hpp>

#include <bb/cascades/Application>
#include <bb/cascades/Container>
#include <bb/cascades/DataModel>
#include <bb/cascades/DropDown>
#include <bb/cascades/QListDataModel>
#include <bb/cascades/TabbedPane>
#include <bb/cascades/ActionBarPlacement>
#include <bb/system/InvokeRequest>
#include "emulator.h"
#include "bbutil.h"
#include <QThread>
#include <QSettings>
#include <QTimer>
#include <QPropertyAnimation>
#include <QAtomicInt>

#include <bb/device/DisplayInfo>

#include <bps/deviceinfo.h>

#include "imageloader.hpp"
#include "NetRequest.hpp"

using namespace bb::cascades;

extern QSettings *m_settings;


class Frontend: public QThread
{
    Q_OBJECT
    Q_PROPERTY(QString rom READ getRom WRITE setRom NOTIFY romChanged)
    Q_PROPERTY(QString startDirectory READ getStartDirectory WRITE setStartDirectory NOTIFY dummySignal)
    Q_PROPERTY(bool hasStartDirectory READ hasStartDirectory CONSTANT)
    Q_PROPERTY(int video READ getVideo WRITE setVideo NOTIFY videoChanged)
    Q_PROPERTY(int audio READ getAudio WRITE setAudio NOTIFY audioChanged)
    Q_PROPERTY(ImageLoader* boxart READ getBoxArt NOTIFY boxArtChanged)
    Q_PROPERTY(bool boxartLoaded READ boxartLoaded NOTIFY boxartLoadedChanged)
    Q_PROPERTY(bool Keyboard READ hasKeyboard CONSTANT)
    Q_PROPERTY(bool useHdmi READ useHdmi WRITE useHdmi NOTIFY dummySignal)
    Q_PROPERTY(int width READ width CONSTANT)
    Q_PROPERTY(int hight READ height CONSTANT)
    Q_PROPERTY(int emuWidth READ emuWidth CONSTANT)
    Q_PROPERTY(int emuHeight READ emuHeight CONSTANT)
	Q_PROPERTY(bb::cascades::DataModel* devices READ devices CONSTANT)
	Q_PROPERTY(bb::cascades::DataModel* history READ history CONSTANT)
	Q_PROPERTY(bool hasHistory READ hasHistory CONSTANT)
	Q_PROPERTY(bool saveHistory READ saveHistory WRITE saveHistory NOTIFY dummySignal)
	Q_PROPERTY(int menuOffset READ menuOffset WRITE menuOffset NOTIFY menuOffsetChanged)
	Q_PROPERTY(bool debugMode READ debugMode CONSTANT)
	Q_PROPERTY(QString coverImage READ coverImage NOTIFY coverImageChanged)
	Q_PROPERTY(QString version READ version CONSTANT)
	Q_PROPERTY(QString lastROM READ lastROM CONSTANT)
	Q_PROPERTY(QString currentROM READ currentROM NOTIFY currentROMChanged)
	Q_PROPERTY(bool isOSThree READ isOSThree CONSTANT)
	Q_PROPERTY(bb::cascades::ActionBarPlacement::Type playPlacement READ playPlacement CONSTANT)
    Q_PROPERTY(bool stretchVideo READ stretchVideo WRITE stretchVideo NOTIFY dummySignal)
	Q_PROPERTY(bool hdmi1080 READ hdmi1080 WRITE hdmi1080 NOTIFY dummySignal)
	Q_PROPERTY(int hdmiResolution READ hdmiResolution WRITE hdmiResolution NOTIFY dummySignal)
	Q_PROPERTY(bool showFPS READ showFPS WRITE showFPS NOTIFY dummySignal)
	Q_PROPERTY(bool rotateQ10 READ rotateQ10 NOTIFY rotationChanged)
	Q_PROPERTY(int numMenuItems READ numMenuItems NOTIFY numMenuItemsChanged)
	Q_PROPERTY(bool noTouchScreenControllers READ noTouchScreenControllers NOTIFY touchScreenControllerCountChanged)

    Q_PROPERTY(int themeIndex READ themeIndex WRITE themeIndex NOTIFY dummySignal)
    Q_PROPERTY(int primaryColourIndex READ primaryColourIndex WRITE primaryColourIndex NOTIFY dummySignal)
    Q_PROPERTY(int primaryColourRed READ primaryColourRed WRITE primaryColourRed NOTIFY dummySignal)
    Q_PROPERTY(int primaryColourGreen READ primaryColourGreen WRITE primaryColourGreen NOTIFY dummySignal)
    Q_PROPERTY(int primaryColourBlue READ primaryColourBlue WRITE primaryColourBlue NOTIFY dummySignal)
    Q_PROPERTY(int baseColourIndex READ baseColourIndex WRITE baseColourIndex NOTIFY dummySignal)
    Q_PROPERTY(int baseColourRed READ baseColourRed WRITE baseColourRed NOTIFY dummySignal)
    Q_PROPERTY(int baseColourGreen READ baseColourGreen WRITE baseColourGreen NOTIFY dummySignal)
    Q_PROPERTY(int baseColourBlue READ baseColourBlue WRITE baseColourBlue NOTIFY dummySignal)

private:
    enum ThemeColor
    {
    	Bright = 2,
    	Dark = 1,
    	Default = 0
    };

public:
    // This is our constructor that sets up the recipe.
    Frontend();
    ~Frontend();

    /* Invokable functions that we can call from QML*/

    /**
     * This Invokable function gets a value from the QSettings,
     * if that value does not exist in the QSettings database, the default value is returned.
     *
     * @param objectName Index path to the item
     * @param defaultValue Used to create the data in the database when adding
     * @return If the objectName exists, the value of the QSettings object is returned.
     *         If the objectName doesn't exist, the default value is returned.
     */
    Q_INVOKABLE
    QString getValueFor(const QString &objectName, const QString &defaultValue);

    /**
     * This function sets a value in the QSettings database. This function should to be called
     * when a data value has been updated from QML
     *
     * @param objectName Index path to the item
     * @param inputValue new value to the QSettings database
     */
    Q_INVOKABLE
    void saveValueFor(const QString &objectName, const QString &inputValue);
    Q_INVOKABLE
    void saveConfigValue(const QString &section, const QString &name, const QString &value);
    Q_INVOKABLE
    QString getConfigValue(const QString &rom, const QString &section, const QString &name, const QString &value);
    Q_INVOKABLE
    void startEmulator(bool start);
    Q_INVOKABLE
    void createCheatsPage();
    Q_INVOKABLE
    void LoadRom();
    Q_INVOKABLE
    int getInputValue(int player, QString value);
    Q_INVOKABLE
    void setInputValue(int player, QString button, int value);
    Q_INVOKABLE
    QString getMogaInputCharacter(int value);
    Q_INVOKABLE
    QString getInputCharacter(int value);
    Q_INVOKABLE
    void setControllerID(int player, QString value);
    Q_INVOKABLE
    QString getControllerID(int player);
    Q_INVOKABLE
    int getControllerIndex(int player);
    Q_INVOKABLE
    void setControllerIndex(int player, int index);
    Q_INVOKABLE
    void setMogaInputValue(int player, QString button, int index);
    Q_INVOKABLE
    int getMogaInputValue(int player, QString button);
    Q_INVOKABLE
    void SaveState();
    Q_INVOKABLE
    void LoadState();
    Q_INVOKABLE
    void LoadTouchOverlay();
    Q_INVOKABLE
    int mapButton();
    Q_INVOKABLE
    void ExitEmulator();
    Q_INVOKABLE
	void loadBoxArt(const QString &url);
    Q_INVOKABLE
    void setBright(int index);
    Q_INVOKABLE
	void removeFromHistory(QString uuid);
    Q_INVOKABLE
	void clearHistory();
    Q_INVOKABLE
    void swipedown();
    Q_INVOKABLE
    void invokeLoadHistoryROM(const QString& rom) { m_historyROM = QString(rom); QTimer::singleShot(0, this, SLOT(onLoadHistoryROM())); }
    Q_INVOKABLE
    void invokePlayHistoryROM(const QString& rom) { m_historyROM = QString(rom); QTimer::singleShot(0, this, SLOT(onPlayHistoryROM())); }
    Q_INVOKABLE
    bool createShortcut(const QString& name, const QString& icon, const QString& location);
    Q_INVOKABLE
    void loadLastROM();
    Q_INVOKABLE
    bool isValidFilename(const QString &filename);
    Q_INVOKABLE
    inline void addMupenMenuItem() { m_numMenuItems.ref(); emit numMenuItemsChanged(); }
    Q_INVOKABLE
    inline void removeMupenMenuItem() { m_numMenuItems.deref(); emit numMenuItemsChanged(); }

    QString getRom();
    int getVideo();
    int getAudio();
    void setRom(QString i);
    void setVideo(int i);
    void setAudio(int i);

signals:
	void romChanged(QString);
	void videoChanged(int);
	void audioChanged(int);
	void boxArtChanged(ImageLoader*);
	void boxartLoadedChanged(bool);
	void dummySignal();
	void hdmiDetected(bool hdmi);
	void hasHistoryChanged();
	void invoked(QString url, bool runnow);
	void menuOffsetChanged();
	void coverImageChanged();
	void createOption(QString name, QUrl imageSource);
	void controllersDetected();
	void loadHistoryROM(QString rom);
	void playHistoryROM(QString rom);
	void currentROMChanged();
	void rotationChanged();
	void numMenuItemsChanged();
	void touchScreenControllerCountChanged();

public slots:
	void addCheatToggle(int);
	void addCheatDropDown(int);
	void onManualExit();
	void onThumbnail();
	void onBoxArtRecieved(const QString &info, bool success);
	void onVersionRecieved(const QString &info, bool success);
	void onInvoke(const bb::system::InvokeRequest& req);
	void showMenuFinished();
	void onMenuOffsetChanged();
	void onCreateOption(QString name, QUrl imageSource);
	void onLoadHistoryROM() { emit loadHistoryROM(m_historyROM); }
	void onPlayHistoryROM() { emit playHistoryROM(m_historyROM); }
	void startEmulatorInternal();
	//void emitSendCheat();
	//void handleSendCheat();

public:
    inline bool hasKeyboard() const { deviceinfo_details_t* details; deviceinfo_get_details(&details); bool retval = deviceinfo_details_get_keyboard(details) == DEVICEINFO_KEYBOARD_PRESENT; deviceinfo_free_details(&details); return retval; }

private:
    inline int width() const { bb::device::DisplayInfo info; return info.pixelSize().width(); }
    inline int height() const { bb::device::DisplayInfo info; return info.pixelSize().height(); }
    inline int emuWidth() const { int w = width(); int h = height(); if (h > w) return h; return w; }
    inline int emuHeight() const { int w = width(); int h = height(); if (h > w) return w; return h; }
    inline QString getStartDirectory() const { return m_settings->value("StartDirectory", "").toString(); }
    inline void setStartDirectory(const QString& dir) { m_settings->setValue("StartDirectory", dir); }
    inline bool hasStartDirectory() const { return (getStartDirectory()).length() > 0; }
    inline bb::cascades::DataModel* devices() const { return m_devices; }
    inline bb::cascades::DataModel* history() const { return m_history; }
    inline bool hasHistory() const { return m_history->size() > 0; }
    inline bool saveHistory() const { return m_settings->value("SAVE_HISTORY", true).toBool(); }
    inline void saveHistory(bool value) { m_settings->setValue("SAVE_HISTORY", value); clearHistory(); }
    inline int menuOffset() const { return m_menuOffset; }
    inline QString coverImage() const { return m_coverImage; }
    inline void menuOffset(int offset) { m_menuOffset = offset; emit menuOffsetChanged(); }
    inline QString version() const { return QString("%1.%2.%3").arg(QString::number(VERSION_MAJOR),
    		QString::number(VERSION_MINOR), QString::number(VERSION_RELEASE)); }
    inline QString lastROM() const { if (!hasHistory()) return ""; return m_history->value(0)["name"].toString(); }
    inline QString currentROM() const { return m_currentROM; }
    inline bool useHdmi() const { return m_useHdmi; }
    inline void useHdmi(bool use) { m_useHdmi = use; }
    inline bool hdmi1080() const { return m_settings->value("HDMI_1080", false).toBool(); }
    inline void hdmi1080(bool use) { m_settings->setValue("HDMI_1080", use); }
    inline int hdmiResolution() const { return m_settings->value("HDMI_RESOLUTION", 4).toInt(); }
    inline void hdmiResolution(int val) { m_settings->setValue("HDMI_RESOLUTION", val); }
    inline bool showFPS() const { return m_settings->value("SHOW_FPS", false).toBool(); }
    inline void showFPS(bool show) { m_settings->setValue("SHOW_FPS", show); }
    inline bool stretchVideo() const { return m_settings->value("STRETCH_VIDEO", true).toBool(); }
    inline void stretchVideo(bool stretch) { m_settings->setValue("STRETCH_VIDEO", stretch); }
    inline bool rotateQ10() const { return q10_rotate; }
    inline int numMenuItems() const { return m_numMenuItems; }
    inline bool noTouchScreenControllers() const { return m_noTouchScreenControllers; }
#ifdef BB103
    inline bool isOSThree() const { return true; }
    inline bool isOSThreeCompiled() const { return true; }
    inline bb::cascades::ActionBarPlacement::Type playPlacement() const { return bb::cascades::ActionBarPlacement::Signature; }
#else
    inline bool isOSThree() const { return m_isOsThree; }
    inline bool isOSThreeCompiled() const { return false; }
    inline bb::cascades::ActionBarPlacement::Type playPlacement() const { if (m_isOsThree) return (bb::cascades::ActionBarPlacement::Type)3; return bb::cascades::ActionBarPlacement::OnBar; }
#endif
    void run();
    Container *createCheatToggle(sCheatInfo *pCur);
    Container *createCheatDropDown(sCheatInfo *pCur);
    void create_button_mapper();
    bool boxartLoaded();
	ImageLoader* getBoxArt();
	void discoverControllers();
	void detectHDMI();
	QList<Game> getHistory();
	void setHistory(QList<Game> list);
	void addToHistory(QString title);
	bool debugMode();

protected:
    inline int themeIndex() const { return m_settings->value("THEME", 0).toInt(); }
    inline int primaryColourIndex() const { return m_settings->value("PRIMARY_COLOUR_INDEX", 1).toInt(); }
    inline int primaryColourRed() const { return m_settings->value("PRIMARY_COLOUR_R", 255).toInt(); }
    inline int primaryColourGreen() const { return m_settings->value("PRIMARY_COLOUR_G", 0).toInt(); }
    inline int primaryColourBlue() const { return m_settings->value("PRIMARY_COLOUR_B", 0).toInt(); }
    inline int baseColourIndex() const { return m_settings->value("BASE_COLOUR_INDEX", 0).toInt(); }
    inline int baseColourRed() const { return m_settings->value("BASE_COLOUR_R", 0).toInt(); }
    inline int baseColourGreen() const { return m_settings->value("BASE_COLOUR_G", 0).toInt(); }
    inline int baseColourBlue() const { return m_settings->value("BASE_COLOUR_B", 255).toInt(); }

    inline void themeIndex(int index) { m_settings->setValue("THEME", index); refreshTheme(); }
    inline void primaryColourIndex(int index) { m_settings->setValue("PRIMARY_COLOUR_INDEX", index); if (index == 1) refreshColours(); }
    inline void primaryColourRed(int value) { m_settings->setValue("PRIMARY_COLOUR_R", value); refreshColours(); }
    inline void primaryColourGreen(int value) { m_settings->setValue("PRIMARY_COLOUR_G", value); refreshColours(); }
    inline void primaryColourBlue(int value) { m_settings->setValue("PRIMARY_COLOUR_B", value); refreshColours(); }
    inline void baseColourIndex(int index) { m_settings->setValue("BASE_COLOUR_INDEX", index); if (index == 1) refreshColours(); }
    inline void baseColourRed(int value) { m_settings->setValue("BASE_COLOUR_R", value); refreshColours(); }
    inline void baseColourGreen(int value) { m_settings->setValue("BASE_COLOUR_G", value); refreshColours(); }
    inline void baseColourBlue(int value) { m_settings->setValue("BASE_COLOUR_B", value); refreshColours(); }

private:
    void refreshColours();
    void refreshTheme();

private:
    bool m_emuRunning;
    int mVideoPlugin;
    QString mRom;
    QMutex *m_animationLock;
    int mAudio;
    Container *mCheatsContainer;
    ImageLoader* m_boxart;
    bb::cascades::TabbedPane *m_tab;
	bool m_boxartLoaded;
    int m_menuOffset;
    QString m_historyROM;
    QString m_coverImage;
    QString m_currentROM;
    int VERSION_MAJOR;
    int VERSION_MINOR;
    int VERSION_RELEASE;
    bb::device::DisplayInfo *m_hdmiInfo;
    bb::cascades::QMapListDataModel* m_devices;
    bb::cascades::QMapListDataModel* m_history;
    QPropertyAnimation* m_menuAnimation;
    bool m_isOsThree;
    bool m_useHdmi;
    QAtomicInt m_numMenuItems;
    bool m_noTouchScreenControllers;
};

#endif // ifndef STARSHIPSETTINGSAPP_H
