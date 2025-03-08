/**
 * dwmconfig.h 
 * Hardware multimedia keys
 */
/* Somewhere at the beginning of config.h include: */

/* 
 You obviously need the X11 development packages installed, X11proto in particular, but 
 here is the location of the upstream copy of the keysyms header if you can't bother 
 using the contents  of your own hard drive. ;-P
 
 https://cgit.freedesktop.org/xorg/proto/x11proto/tree/XF86keysym.h
*/

#include <X11/XF86keysym.h>

/* Add somewhere in your constants definition section */
//static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
//static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
//static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };

//static const char *upvol[]   = { "amixer", "-q", "set", "Master", "5%+", "unmute", NULL };
//static const char *downvol[] = { "amixer", "-q", "set", "Master", "5%-", "unmute", NULL };
//static const char *mutevol[] = { "amixer", "-q", "set", "Master", "toggle", NULL };

/* If you use amixer, use this instead. Thanks go to DaniOrt3ga. */
static const char *upvol[] = { "/usr/bin/amixer", "set", "Master", "5%+", NULL };
static const char *downvol[] = { "/usr/bin/amixer", "set", "Master", "5%-", NULL };
static const char *mutevol[] = { "/usr/bin/amixerl", "set", "Master", "toggle", NULL };

/* To use light add this to the constant definition section. Thanks Hritik14. */
//static const char *light_up[] = {"/usr/bin/light", "-A", "5", NULL};
//static const char *light_down[] = {"/usr/bin/light", "-U", "5", NULL};


/* Add to keys[] array. With 0 as modifier, you are able to use the keys directly. */
static Key keys[] = {
	{ 0,                       XF86XK_AudioLowerVolume, spawn, {.v = downvol } }
	{ 0,                       XF86XK_AudioMute, spawn, {.v = mutevol } }
	{ 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } }
};

/* If you have a small laptop keyboard or don't want to spring your fingers too far away. */
//static Key keys[] = {
//	{ MODKEY,                       XK_F11, spawn, {.v = downvol } },
//	{ MODKEY,                       XK_F9,  spawn, {.v = mutevol } },
//	{ MODKEY,                       XK_F12, spawn, {.v = upvol   } },
//};

/* To use light add this to the keys[] array. Thanks Hritik14. */
//static Key keys[] = {
//	{ 0,				XF86XK_MonBrightnessUp,		spawn,	{.v = light_up} },
//	{ 0,				XF86XK_MonBrightnessDown,	spawn,	{.v = light_down} },
//};
