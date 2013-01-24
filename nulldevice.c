/*
 * nulldevice.c: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id$
 */

#include <vdr/config.h>
#include <vdr/device.h>
#include <vdr/osd.h>
#include <vdr/plugin.h>

static const char *VERSION        = "2.0.0";
static const char *DESCRIPTION    = tr("experimental fork of dummydevice");
static const char *MAINMENUENTRY  = NULL;


class cNullOsd : public cOsd {
  public:
    cNullOsd(int Left, int Top, uint Level) : cOsd(Left, Top, Level) {}
    virtual ~cNullOsd() {}

    virtual cPixmap *CreatePixmap(int Layer, const cRect &ViewPort, const cRect &DrawPort = cRect::Null) {return NULL;}
    virtual void DestroyPixmap(cPixmap *Pixmap) {}
    virtual void DrawImage(const cPoint &Point, const cImage &Image) {}
    virtual void DrawImage(const cPoint &Point, int ImageHandle) {}
    virtual eOsdError CanHandleAreas(const tArea *Areas, int NumAreas) {return oeOk;}
    virtual eOsdError SetAreas(const tArea *Areas, int NumAreas) {return oeOk;}
    virtual void SaveRegion(int x1, int y1, int x2, int y2) {}
    virtual void RestoreRegion(void) {}
    virtual eOsdError SetPalette(const cPalette &Palette, int Area) {return oeOk;}
    virtual void DrawPixel(int x, int y, tColor Color) {}
    virtual void DrawBitmap(int x, int y, const cBitmap &Bitmap, tColor ColorFg = 0, tColor ColorBg = 0, bool ReplacePalette = false, bool Overlay = false) {}
    virtual void DrawText(int x, int y, const char *s, tColor ColorFg, tColor ColorBg, const cFont *Font, int Width = 0, int Height = 0, int Alignment = taDefault) {}
    virtual void DrawRectangle(int x1, int y1, int x2, int y2, tColor Color) {}
    virtual void DrawEllipse(int x1, int y1, int x2, int y2, tColor Color, int Quadrants = 0) {}
    virtual void DrawSlope(int x1, int y1, int x2, int y2, tColor Color, int Type) {}
    virtual void Flush(void) {}
};

class cNullOsdProvider : public cOsdProvider {
  protected:
    virtual cOsd *CreateOsd(int Left, int Top, uint Level) { return new cNullOsd(Left, Top, Level); }
    virtual bool ProvidesTrueColor(void) {return true;}
    virtual int StoreImageData(const cImage &Image) {return 0;}
    virtual void DropImageData(int ImageHandle) {}

  public:
    cNullOsdProvider() : cOsdProvider() {}
    virtual ~cNullOsdProvider() {}
};


class cNullDevice : cDevice {
public:
    cNullDevice() : cDevice() {}
    virtual ~cNullDevice() {}

    virtual bool HasDecoder(void) const { return true; }

    virtual bool SetPlayMode(ePlayMode PlayMode) { return true; }
    virtual int  PlayVideo(const uchar *Data, int Length) { return Length; }

    virtual int  PlayAudio(const uchar *Data, int Length, uchar Id) { return Length; }

    virtual bool Poll(cPoller &Poller, int TimeoutMs = 0) { return true; }
    virtual bool Flush(int TimeoutMs = 0) { return true; }
    bool Start(void) {return true;}

  protected:
    virtual void MakePrimaryDevice(bool On) { if (On) new cNullOsdProvider(); cDevice::MakePrimaryDevice(On); }
};


class cPluginNulldevice : public cPlugin {
private:
  // Add any member variables or functions you may need here.
public:
  cPluginNulldevice(void);
  virtual ~cPluginNulldevice();
  virtual const char *Version(void) { return VERSION; }
  virtual const char *Description(void) { return DESCRIPTION; }
  virtual const char *CommandLineHelp(void);
  virtual bool ProcessArgs(int argc, char *argv[]);
  virtual bool Initialize(void);
  virtual bool Start(void);
  virtual void Stop(void);
  virtual void Housekeeping(void);
  virtual void MainThreadHook(void);
  virtual cString Active(void);
  virtual time_t WakeupTime(void);
  virtual const char *MainMenuEntry(void) { return MAINMENUENTRY; }
  virtual cOsdObject *MainMenuAction(void);
  virtual cMenuSetupPage *SetupMenu(void);
  virtual bool SetupParse(const char *Name, const char *Value);
  virtual bool Service(const char *Id, void *Data = NULL);
  virtual const char **SVDRPHelpPages(void);
  virtual cString SVDRPCommand(const char *Command, const char *Option, int &ReplyCode);
  };

cPluginNulldevice::cPluginNulldevice(void)
{
  // Initialize any member variables here.
  // DON'T DO ANYTHING ELSE THAT MAY HAVE SIDE EFFECTS, REQUIRE GLOBAL
  // VDR OBJECTS TO EXIST OR PRODUCE ANY OUTPUT!
}

cPluginNulldevice::~cPluginNulldevice()
{
  // Clean up after yourself!
}

const char *cPluginNulldevice::CommandLineHelp(void)
{
  // Return a string that describes all known command line options.
  return NULL;
}

bool cPluginNulldevice::ProcessArgs(int argc, char *argv[])
{
  // Implement command line argument processing here if applicable.
  return true;
}

bool cPluginNulldevice::Initialize(void)
{
  // Initialize any background activities the plugin shall perform.
  new cNullDevice();
  return true;
}

bool cPluginNulldevice::Start(void)
{
  // Start any background activities the plugin shall perform.
  return true;
}

void cPluginNulldevice::Stop(void)
{
  // Stop any background activities the plugin is performing.
}

void cPluginNulldevice::Housekeeping(void)
{
  // Perform any cleanup or other regular tasks.
}

void cPluginNulldevice::MainThreadHook(void)
{
  // Perform actions in the context of the main program thread.
  // WARNING: Use with great care - see PLUGINS.html!
}

cString cPluginNulldevice::Active(void)
{
  // Return a message string if shutdown should be postponed
  return NULL;
}

time_t cPluginNulldevice::WakeupTime(void)
{
  // Return custom wakeup time for shutdown script
  return 0;
}

cOsdObject *cPluginNulldevice::MainMenuAction(void)
{
  // Perform the action when selected from the main VDR menu.
  return NULL;
}

cMenuSetupPage *cPluginNulldevice::SetupMenu(void)
{
  // Return a setup menu in case the plugin supports one.
  return NULL;
}

bool cPluginNulldevice::SetupParse(const char *Name, const char *Value)
{
  // Parse your own setup parameters and store their values.
  return false;
}

bool cPluginNulldevice::Service(const char *Id, void *Data)
{
  // Handle custom service requests from other plugins
  return false;
}

const char **cPluginNulldevice::SVDRPHelpPages(void)
{
  // Return help text for SVDRP commands this plugin implements
  return NULL;
}

cString cPluginNulldevice::SVDRPCommand(const char *Command, const char *Option, int &ReplyCode)
{
  // Process SVDRP commands this plugin implements
  return NULL;
}

VDRPLUGINCREATOR(cPluginNulldevice); // Don't touch this!
