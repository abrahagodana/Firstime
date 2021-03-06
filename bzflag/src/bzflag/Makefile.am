if CLIENT_INCLUDED
bin_PROGRAMS = bzflag
endif

MAINTAINERCLEANFILES = \
	Makefile.in

if HAVE_KRB5
KRB5 =	ClientAuthentication.cxx	\
	ClientAuthentication.h		\
	LoginMenu.cxx			\
	LoginMenu.h
endif

bzflag_SOURCES =			\
	ActionBinding.cxx		\
	ActionBinding.h			\
	AudioMenu.cxx			\
	AudioMenu.h			\
	AutoPilot.cxx			\
	BackgroundRenderer.cxx		\
	BackgroundRenderer.h		\
	BaseLocalPlayer.cxx		\
	BaseLocalPlayer.h		\
	ComposeDefaultKey.cxx		\
	ComposeDefaultKey.h		\
	ControlPanel.cxx		\
	ControlPanel.h			\
	DisplayMenu.cxx			\
	DisplayMenu.h			\
	EffectsMenu.cxx			\
	EffectsMenu.h			\
	EntryZone.cxx			\
	EntryZone.h			\
	FlashClock.cxx			\
	FlashClock.h			\
	ForceFeedback.cxx		\
	ForceFeedback.h			\
	FormatMenu.cxx			\
	FormatMenu.h			\
	GuidedMissleStrategy.cxx	\
	GuidedMissleStrategy.h		\
	GUIOptionsMenu.cxx		\
	GUIOptionsMenu.h		\
	HelpMenu.cxx			\
	HelpMenu.h			\
	HUDDialog.cxx			\
	HUDDialog.h			\
	HUDDialogStack.cxx		\
	HUDDialogStack.h		\
	HUDRenderer.cxx			\
	HUDRenderer.h			\
	HUDui.cxx			\
	HUDui.h				\
	HUDuiControl.cxx		\
	HUDuiControl.h			\
	HUDuiDefaultKey.cxx		\
	HUDuiDefaultKey.h		\
	HUDuiLabel.cxx			\
	HUDuiLabel.h			\
	HUDuiList.cxx			\
	HUDuiList.h			\
	HUDuiTextureLabel.cxx		\
	HUDuiTextureLabel.h		\
	HUDuiTypeIn.cxx			\
	HUDuiTypeIn.h			\
	JoinMenu.cxx			\
	JoinMenu.h			\
	InputMenu.cxx			\
	InputMenu.h			\
	KeyboardMapMenu.cxx		\
	KeyboardMapMenu.h		\
	LocalPlayer.cxx			\
	LocalPlayer.h			\
	MainMenu.cxx			\
	MainMenu.h			\
	MainWindow.cxx			\
	MainWindow.h			\
	MenuDefaultKey.h		\
	MenuDefaultKey.cxx		\
	motd.h				\
	motd.cxx			\
	OptionsMenu.cxx			\
	OptionsMenu.h			\
	Player.cxx			\
	Player.h			\
	Plan.cxx			\
	Plan.h			\
	QuickKeysMenu.cxx		\
	QuickKeysMenu.h			\
	QuitMenu.cxx			\
	QuitMenu.h			\
	RadarRenderer.cxx		\
	RadarRenderer.h			\
	Region.cxx			\
	Region.h			\
	RegionPriorityQueue.cxx		\
	RegionPriorityQueue.h		\
	RemotePlayer.cxx		\
	RemotePlayer.h			\
	RobotPlayer.cxx			\
	RobotPlayer.h			\
	RoofTops.cxx			\
	RoofTops.h			\
	Roster.cxx			\
	Roster.h			\
	SaveWorldMenu.cxx		\
	SaveWorldMenu.h			\
	SceneBuilder.cxx		\
	SceneBuilder.h			\
	SceneRenderer.cxx		\
	SegmentedShotStrategy.cxx	\
	SegmentedShotStrategy.h		\
	ServerCommandKey.cxx		\
	ServerCommandKey.h		\
	ServerLink.cxx			\
	ServerLink.h			\
	ServerMenu.cxx			\
	ServerMenu.h			\
	ServerStartMenu.cxx		\
	ServerStartMenu.h		\
	ShockWaveStrategy.cxx		\
	ShockWaveStrategy.h		\
	ShotPath.cxx			\
	ShotPath.h			\
	ShotPathSegment.cxx		\
	ShotPathSegment.h		\
	ShotStats.cxx			\
	ShotStats.h			\
	ShotStatsDefaultKey.cxx		\
	ShotStatsDefaultKey.h		\
	ShotStatistics.h		\
	ShotStatistics.cxx		\
	ShotStrategy.cxx		\
	ShotStrategy.h			\
	SilenceDefaultKey.cxx		\
	SilenceDefaultKey.h		\
	TargetingUtils.cxx		\
	TargetingUtils.h		\
	TrackMarks.cxx			\
	TrackMarks.h			\
	Weapon.cxx			\
	Weapon.h			\
	WeatherRenderer.h		\
	WeatherRenderer.cxx		\
	World.cxx			\
	World.h				\
	WorldBuilder.cxx		\
	WorldBuilder.h			\
	WorldPlayer.cxx			\
	WorldPlayer.h			\
	bzflag.cxx			\
	callbacks.cxx			\
	callbacks.h			\
	clientCommands.cxx		\
	commands.h			\
	daylight.cxx			\
	daylight.h			\
	playing.cxx			\
	playing.h			\
	sound.cxx			\
	sound.h				\
	stars.cxx			\
	stars.h				\
	$(KRB5)


if WIN32
RESOURCE = bzflag.res
else
RESOURCE =
endif

if BUILDZLIB
ZLIB = ../zlib/libz.a
else
ZLIB = -lz
endif

if MACOS
NACLIB =	\
	../platform/MacOSX/libMac.a
endif

if BUILD_REGEX
REGEX = \
	../regex/libregex.a
endif

LDADD =	\
	../3D/lib3D.a			\
	../common/libCommon.a		\
	../game/libGame.a		\
	../net/libNet.a			\
	../obstacle/libObstacle.a	\
	$(NACLIB)			\
	../platform/libPlatform.a	\
	../ogl/libGLKit.a		\
	../scene/libSceneDB.a		\
	../geometry/libGeometry.a	\
	../mediafile/libMediaFile.a	\
	$(REGEX)			\
	$(ZLIB)				\
	$(KRB5_LIBS)			\
	$(RESOURCE)			\
	$(SDL_LIBS)			\
	$(CURL_LIBS)			\
	$(GLIBS)			\
	../date/libDate.a
# This is required to hook in ogg/vorbis libraries
#	$(ALIBS)

AM_CPPFLAGS = -I$(top_srcdir)/include $(X_CFLAGS) $(SDL_CFLAGS)

bzflag.res: $(top_srcdir)/win32/bzflag.rc $(top_srcdir)/win32/bzflag.ico
	$(WINDRES) --include-dir=$(top_srcdir)/win32/ -i $(top_srcdir)/win32/bzflag.rc -o bzflag.res \
	-O coff
