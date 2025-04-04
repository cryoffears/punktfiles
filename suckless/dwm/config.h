/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 1.7;      /* border pixel of windows */
static unsigned int gappx     = 3.3;      /* gaps size between windows  */
static unsigned int snap      = 32;       /* snap pixel */
static unsigned int gappih    = 20;       /* horiz inner gap between windows */
static unsigned int gappiv    = 10;       /* vert inner gap between windows */
static unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */

static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 4.6;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;   /* 0 means no systray */

static const char *fonts[]          = { "SF Pro Text:size=11.5", "fontawesome:size=11.3", "Hack Nerd Font:size=11.3", "NotoColorEmoji:pixelsize=11.3:antialias=true:autohint=true", "joypixels:size=11.3", "fontello:size=11.3", "font-logos:size=11.3" };
static const char dmenufont[]       = "SF Pro Text:size=11.6";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#999999";
static const char col_gray3[]       = "#eeeeee";
static const char col_gray4[]       = "#dddddd";
static const char col_cyan[]        = "#ff7700";
static const char col_black[]	    = "#000000";
static const char col_white[]       = "#ffffff";
static const char col_purple[]	    = "#ff7700";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "", "" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
    { "Gimp",       NULL,       NULL,       1 << 7,       0,           -1 },
    { "Krita",       NULL,       NULL,       1 << 7,       0,           -1 },
    { "Firefox",    NULL,       NULL,       1 << 2,       0,           -1 },
    { "LibreWolf",  NULL,       NULL,       1 << 2,       0,           -1 },
    { "Brave",      NULL,       NULL,       1 << 2,       0,           -1 },
    { "Chromium",   NULL,       NULL,       1 << 2,       0,           -1 },
    { "Qutebrowser",    NULL,   NULL,	    1 << 2,       0,           -1 },
    { "Discord",        NULL,   NULL,	    1 << 4,       0,           -1 },
    { "Steam",         NULL,   NULL,        1 << 0,       0,           -1 },
    { "Virt-Manager",   NULL,  NULL,	    1 << 8,       0,           -1 },
    { "Nuclear",       NULL,    NULL,	    1 << 5,       0,           -1 },
    { "Rhythmbox",       NULL,  NULL,       1 << 5,       0,           -1 },
    { "KeePassXC",      NULL,   NULL,	    1 << 9,       0,           -1 },
    { "OBS",        NULL,       NULL,       1 << 8,       0,           -1 },
  	{ "ClipGrab",   NULL,       NULL,       1 << 2,       0,           -1 },
    { "Dolphin",    NULL,       NULL,       1 << 3,       0,           -1 },
    { "Tor Browser",    NULL,   NULL,       1 << 6,       0,           -1 },
    { "Spotify",   NULL,        NULL,       1 << 5,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_black, "-nf", col_gray3, "-sb", col_purple, "-sf", col_black,  NULL };
static const char *termcmd[]  = { "kitty", NULL }; // { "alacritty", NULL };
static const char *librewolfcmd[]  = { "librewolf", NULL };
static const char *musicmd[]  = { "rhythmbox", NULL };
static const char *discordcmd[] = { "discord", NULL };
static const char *passcmd[] = { "keepassxc", NULL };

/* volume controls */
static const char *upvol[]   = { "amixer", "-q", "set", "Master", "5%+", "unmute", NULL };
static const char *downvol[] = { "amixer", "-q", "set", "Master", "5%-", "unmute", NULL };
static const char *mutevol[] = { "amixer", "-q", "set", "Master", "toggle", NULL };

#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_d,       spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,  spawn,          {.v = termcmd } },
    { MODKEY,                       XK_m,       spawn,          {.v = librewolfcmd } },
    { MODKEY,                       XK_n,       spawn,          {.v = discordcmd } },
    { MODKEY,                       XK_F3,      spawn,          {.v = passcmd } },
    { MODKEY,                       XK_F5,      spawn,          {.v = musicmd } },
	{ MODKEY,                       XK_t,       togglebar,      {0} },
	{ MODKEY,                       XK_j,       focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,       focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,       incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,       incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,       setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,       setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,       zoom,           {0} },
	{ MODKEY,                       XK_Tab,     view,           {0} },
	{ MODKEY, 	                    XK_c,       killclient,     {0} },
	{ MODKEY,                       XK_r,       setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,       setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,       setlayout,      {.v = &layouts[2]} },
    { MODKEY|ShiftMask,             XK_f,       togglefullscr,  {0} },
	{ MODKEY,                       XK_space,   setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,   togglefloating, {0} },
	{ MODKEY,                       XK_0,       view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,       tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,  tagmon,         {.i = +1 } },
    { MODKEY,              		    XK_b,       shiftview,  	   { .i = +1 } },
	{ MODKEY,              		    XK_v,       shiftview,      { .i = -1 } },
    { MODKEY,                       XK_minus,   setgaps,        {.i = -1 } },
    { MODKEY,                       XK_equal,   setgaps,        {.i = +1 } },
    { MODKEY|ShiftMask,             XK_equal,   setgaps,        {.i = 0  } },
 	//{ MODKEY,                       XK_F8,      spawn,          {.v = upvol   } },
 	//{ MODKEY,                       XK_F7,      spawn,          {.v = downvol } },
 	//{ MODKEY,                       XK_F5,      spawn,          {.v = mutevol } },
 	TAGKEYS(                        XK_1,                       0)
	TAGKEYS(                        XK_2,                       1)
	TAGKEYS(                        XK_3,                       2)
	TAGKEYS(                        XK_4,                       3)
	TAGKEYS(                        XK_5,                       4)
	TAGKEYS(                        XK_6,                       5)
	TAGKEYS(                        XK_7,                       6)
	TAGKEYS(                        XK_8,                       7)
	TAGKEYS(                        XK_9,                       8)
	{ MODKEY|ShiftMask,             XK_q,       quit,           {0} },

/* Numpad & Diff Hotkeys */

	TAGKEYS(                        XK_KP_End,                    0)
	TAGKEYS(                        XK_KP_Down,                   1)
	TAGKEYS(                        XK_KP_Page_Down,              2)
	TAGKEYS(                        XK_KP_Left,                   3)
	TAGKEYS(                        XK_KP_Begin,                  4)
	TAGKEYS(                        XK_KP_Right,                  5)
	TAGKEYS(                        XK_KP_Home,                   6)
	TAGKEYS(                        XK_KP_Up,                     7)
	TAGKEYS(                        XK_KP_Page_Up,                8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

