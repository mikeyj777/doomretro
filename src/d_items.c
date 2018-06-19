/*
========================================================================

                           D O O M  R e t r o
         The classic, refined DOOM source port. For Windows PC.

========================================================================

  Copyright © 1993-2012 id Software LLC, a ZeniMax Media company.
  Copyright © 2013-2018 Brad Harding.

  DOOM Retro is a fork of Chocolate DOOM. For a list of credits, see
  <https://github.com/bradharding/doomretro/wiki/CREDITS>.

  This file is part of DOOM Retro.

  DOOM Retro is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation, either version 3 of the License, or (at your
  option) any later version.

  DOOM Retro is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with DOOM Retro. If not, see <https://www.gnu.org/licenses/>.

  DOOM is a registered trademark of id Software LLC, a ZeniMax Media
  company, in the US and/or other countries and is used without
  permission. All other trademarks are the property of their respective
  holders. DOOM Retro is in no way affiliated with nor endorsed by
  id Software.

========================================================================
*/

#include "d_items.h"
#include "info.h"
#include "states.h"

weaponinfo_t weaponinfo[NUMWEAPONS] =
{
    {
        /* description */  "fist",
        /* ammotype */     am_noammo,
        /* priority */     -1,
        /* minammo */      0,
        /* upstate */      S_PUNCHUP,
        /* downstate */    S_PUNCHDOWN,
        /* readystate */   S_PUNCH,
        /* atkstate */     S_PUNCH1,
        /* holdatkstate */ S_PUNCH1,
        /* flashstate */   S_NULL,
        /* recoil */       0,
        /* motorspeed */   37500,
        /* tics */         10,
        /* prev */         wp_bfg,
        /* next */         wp_chainsaw,
        /* lookup */       1472,
        /* lookdown */     1472
    },

    {
        /* description */  "pistol",
        /* ammotype */     am_clip,
        /* priority */     -1,
        /* minammo */      1,
        /* upstate */      S_PISTOLUP,
        /* downstate */    S_PISTOLDOWN,
        /* readystate */   S_PISTOL,
        /* atkstate */     S_PISTOL1,
        /* holdatkstate */ S_PISTOL1,
        /* flashstate */   S_PISTOLFLASH,
        /* recoil */       4,
        /* motorspeed */   45000,
        /* tics */         10,
        /* prev */         wp_chainsaw,
        /* next */         wp_shotgun,
        /* lookup */       1472,
        /* lookdown */     1472
    },

    {
        /* description */  "shotgun",
        /* ammotype */     am_shell,
        /* priority */     -1,
        /* minammo */      1,
        /* upstate */      S_SGUNUP,
        /* downstate */    S_SGUNDOWN,
        /* readystate */   S_SGUN,
        /* atkstate */     S_SGUN1,
        /* holdatkstate */ S_SGUN1,
        /* flashstate */   S_SGUNFLASH1,
        /* recoil */       8,
        /* motorspeed */   52500,
        /* tics */         10,
        /* prev */         wp_pistol,
        /* next */         wp_supershotgun,
        /* lookup */       1472,
        /* lookdown */     1472
    },

    {
        /* description */  "chaingun",
        /* ammotype */     am_clip,
        /* priority */     -1,
        /* minammo */      1,
        /* upstate */      S_CHAINUP,
        /* downstate */    S_CHAINDOWN,
        /* readystate */   S_CHAIN,
        /* atkstate */     S_CHAIN1,
        /* holdatkstate */ S_CHAIN1,
        /* flashstate */   S_CHAINFLASH1,
        /* recoil */       4,
        /* motorspeed */   45000,
        /* tics */         10,
        /* prev */         wp_supershotgun,
        /* next */         wp_missile,
        /* lookup */       1472,
        /* lookdown */     1472
    },

    {
        /* description */  "rocket launcher",
        /* ammotype */     am_misl,
        /* priority */     -1,
        /* minammo */      1,
        /* upstate */      S_MISSILEUP,
        /* downstate */    S_MISSILEDOWN,
        /* readystate */   S_MISSILE,
        /* atkstate */     S_MISSILE1,
        /* holdatkstate */ S_MISSILE1,
        /* flashstate */   S_MISSILEFLASH1,
        /* recoil */       16,
        /* motorspeed */   60000,
        /* tics */         20,
        /* prev */         wp_chaingun,
        /* next */         wp_plasma,
        /* lookup */       1472,
        /* lookdown */     1472
    },

    {
        /* description */  "plasma rifle",
        /* ammotype */     am_cell,
        /* priority */     -1,
        /* minammo */      1,
        /* upstate */      S_PLASMAUP,
        /* downstate */    S_PLASMADOWN,
        /* readystate */   S_PLASMA,
        /* atkstate */     S_PLASMA1,
        /* holdatkstate */ S_PLASMA1,
        /* flashstate */   S_PLASMAFLASH1,
        /* recoil */       4,
        /* motorspeed */   52500,
        /* tics */         10,
        /* prev */         wp_missile,
        /* next */         wp_bfg,
        /* lookup */       1472,
        /* lookdown */     1472
    },

    {
        /* description */  "BFG-9000",
        /* ammotype */     am_cell,
        /* priority */     -1,
        /* minammo */      BFGCELLS,
        /* upstate */      S_BFGUP,
        /* downstate */    S_BFGDOWN,
        /* readystate */   S_BFG,
        /* atkstate */     S_BFG1,
        /* holdatkstate */ S_BFG1,
        /* flashstate */   S_BFGFLASH1,
        /* recoil */       20,
        /* motorspeed */   45000,
        /* tics */         30,
        /* prev */         wp_plasma,
        /* next */         wp_fist,
        /* lookup */       1472,
        /* lookdown */     1472
    },

    {
        /* description */  "chainsaw",
        /* ammotype */     am_noammo,
        /* priority */     -1,
        /* minammo */      0,
        /* upstate */      S_SAWUP,
        /* downstate */    S_SAWDOWN,
        /* readystate */   S_SAW,
        /* atkstate */     S_SAW1,
        /* holdatkstate */ S_SAW1,
        /* flashstate */   S_NULL,
        /* recoil */       -2,
        /* motorspeed */   45000,
        /* tics */         10,
        /* prev */         wp_fist,
        /* next */         wp_pistol,
        /* lookup */       1472,
        /* lookdown */     1472
    },

    {
        /* description */  "super shotgun",
        /* ammotype */     am_shell,
        /* priority */     -1,
        /* minammo */      2,
        /* upstate */      S_DSGUNUP,
        /* downstate */    S_DSGUNDOWN,
        /* readystate */   S_DSGUN,
        /* atkstate */     S_DSGUN1,
        /* holdatkstate */ S_DSGUN1,
        /* flashstate */   S_DSGUNFLASH1,
        /* recoil */       16,
        /* motorspeed */   60000,
        /* tics */         10,
        /* prev */         wp_shotgun,
        /* next */         wp_chaingun,
        /* lookup */       1472,
        /* lookdown */     1472
    }
};

weaponinfo_t wpnlev1info[NUMHWEAPONS] =
{
    {
        /* description */  "staff",
        /* ammotype */     am_noammo,
        /* priority */     1,
        /* minammo */      0,
        /* upstate */      HS_STAFFUP,
        /* downstate */    HS_STAFFDOWN,
        /* readystate */   HS_STAFFREADY,
        /* atkstate */     HS_STAFFATK1_1,
        /* holdatkstate */ HS_STAFFATK1_1,
        /* flashstate */   HS_NULL,
        /* recoil */       0,
        /* motorspeed */   0,
        /* tics */         0,
        /* prev */         (weapontype_t)wp_beak,
        /* next */         (weapontype_t)wp_gauntlets,
        /* lookup */       1472,
        /* lookdown */     1472
    },

    {
        /* description */  "gold wand",
        /* ammotype */     am_goldwand,
        /* priority */     3,
        /* minammo */      0,
        /* upstate */      HS_GOLDWANDUP,
        /* downstate */    HS_GOLDWANDDOWN,
        /* readystate */   HS_GOLDWANDREADY,
        /* atkstate */     HS_GOLDWANDATK1_1,
        /* holdatkstate */ HS_GOLDWANDATK1_1,
        /* flashstate */   HS_NULL,
        /* recoil */       0,
        /* motorspeed */   0,
        /* tics */         0,
        /* prev */         (weapontype_t)wp_gauntlets,
        /* next */         (weapontype_t)wp_crossbow,
        /* lookup */       1472,
        /* lookdown */     1472
    },

    {
        /* description */  "crossbow",
        /* ammotype */     am_crossbow,
        /* priority */     4,
        /* minammo */      0,
        /* upstate */      HS_CRBOWUP,
        /* downstate */    HS_CRBOWDOWN,
        /* readystate */   HS_CRBOW1,
        /* atkstate */     HS_CRBOWATK1_1,
        /* holdatkstate */ HS_CRBOWATK1_1,
        /* flashstate */   HS_NULL,
        /* recoil */       0,
        /* motorspeed */   0,
        /* tics */         0,
        /* prev */         (weapontype_t)wp_goldwand,
        /* next */         (weapontype_t)wp_blaster,
        /* lookup */       1472,
        /* lookdown */     184
    },

    {
        /* description */  "blaster",
        /* ammotype */     am_blaster,
        /* priority */     5,
        /* minammo */      0,
        /* upstate */      HS_BLASTERUP,
        /* downstate */    HS_BLASTERDOWN,
        /* readystate */   HS_BLASTERREADY,
        /* atkstate */     HS_BLASTERATK1_1,
        /* holdatkstate */ HS_BLASTERATK1_3,
        /* flashstate */   HS_NULL,
        /* recoil */       0,
        /* motorspeed */   0,
        /* tics */         0,
        /* prev */         (weapontype_t)wp_crossbow,
        /* next */         (weapontype_t)wp_skullrod,
        /* lookup */       1472,
        /* lookdown */     1472
    },

    {
        /* description */  "skull rod",
        /* ammotype */     am_skullrod,
        /* priority */     6,
        /* minammo */      0,
        /* upstate */      HS_HORNRODUP,
        /* downstate */    HS_HORNRODDOWN,
        /* readystate */   HS_HORNRODREADY,
        /* atkstate */     HS_HORNRODATK1_1,
        /* holdatkstate */ HS_HORNRODATK1_1,
        /* flashstate */   HS_NULL,
        /* recoil */       0,
        /* motorspeed */   0,
        /* tics */         0,
        /* prev */         wp_blaster,
        /* next */         wp_phoenixrod,
        /* lookup */       1472,
        /* lookdown */     182
    },

    {
        /* description */  "phoenix rod",
        /* ammotype */     am_phoenixrod,
        /* priority */     7,
        /* minammo */      0,
        /* upstate */      HS_PHOENIXUP,
        /* downstate */    HS_PHOENIXDOWN,
        /* readystate */   HS_PHOENIXREADY,
        /* atkstate */     HS_PHOENIXATK1_1,
        /* holdatkstate */ HS_PHOENIXATK1_1,
        /* flashstate */   HS_NULL,
        /* recoil */       0,
        /* motorspeed */   0,
        /* tics */         0,
        /* prev */         wp_skullrod,
        /* next */         wp_mace,
        /* lookup */       1472,
        /* lookdown */     182
    },

    {
        /* description */  "mace",
        /* ammotype */     am_mace,
        /* priority */     8,
        /* minammo */      0,
        /* upstate */      HS_MACEUP,
        /* downstate */    HS_MACEDOWN,
        /* readystate */   HS_MACEREADY,
        /* atkstate */     HS_MACEATK1_1,
        /* holdatkstate */ HS_MACEATK1_2,
        /* flashstate */   HS_NULL,
        /* recoil */       0,
        /* motorspeed */   0,
        /* tics */         0,
        /* prev */         wp_phoenixrod,
        /* next */         wp_beak,
        /* lookup */       1472,
        /* lookdown */     736
    },

    {
        /* description */  "gauntlets",
        /* ammotype */     am_noammo,
        /* priority */     2,
        /* minammo */      0,
        /* upstate */      HS_GAUNTLETUP,
        /* downstate */    HS_GAUNTLETDOWN,
        /* readystate */   HS_GAUNTLETREADY,
        /* atkstate */     HS_GAUNTLETATK1_1,
        /* holdatkstate */ HS_GAUNTLETATK1_3,
        /* flashstate */   HS_NULL,
        /* recoil */       0,
        /* motorspeed */   0,
        /* tics */         0,
        /* prev */         wp_staff,
        /* next */         wp_goldwand,
        /* lookup */       1472,
        /* lookdown */     368
    },

    {
        /* description */  "beak",
        /* ammotype */     am_noammo,
        /* priority */     0,
        /* minammo */      0,
        /* upstate */      HS_BEAKUP,
        /* downstate */    HS_BEAKDOWN,
        /* readystate */   HS_BEAKREADY,
        /* atkstate */     HS_BEAKATK1_1,
        /* holdatkstate */ HS_BEAKATK1_1,
        /* flashstate */   HS_NULL,
        /* recoil */       0,
        /* motorspeed */   0,
        /* tics */         0,
        /* prev */         wp_mace,
        /* next */         wp_staff,
        /* lookup */       1472,
        /* lookdown */     182
    }
};

weaponinfo_t wpnlev2info[NUMHWEAPONS] =
{
    {
        /* description */  "staff",
        /* ammotype */     am_noammo,
        /* priority */     1,
        /* minammo */      0,
        /* upstate */      HS_STAFFUP2,
        /* downstate */    HS_STAFFDOWN2,
        /* readystate */   HS_STAFFREADY2_1,
        /* atkstate */     HS_STAFFATK2_1,
        /* holdatkstate */ HS_STAFFATK2_1,
        /* flashstate */   HS_NULL,
        /* recoil */       0,
        /* motorspeed */   0,
        /* tics */         0,
        /* prev */         wp_beak,
        /* next */         wp_gauntlets,
        /* lookup */       1472,
        /* lookdown */     1472
    },

    {
        /* description */  "gold wand",
        /* ammotype */     am_goldwand,
        /* priority */     3,
        /* minammo */      0,
        /* upstate */      HS_GOLDWANDUP,
        /* downstate */    HS_GOLDWANDDOWN,
        /* readystate */   HS_GOLDWANDREADY,
        /* atkstate */     HS_GOLDWANDATK2_1,
        /* holdatkstate */ HS_GOLDWANDATK2_1,
        /* flashstate */   HS_NULL,
        /* recoil */       0,
        /* motorspeed */   0,
        /* tics */         0,
        /* prev */         wp_gauntlets,
        /* next */         wp_crossbow,
        /* lookup */       1472,
        /* lookdown */     1472
    },

    {
        /* description */  "crossbow",
        /* ammotype */     am_crossbow,
        /* priority */     4,
        /* minammo */      0,
        /* upstate */      HS_CRBOWUP,
        /* downstate */    HS_CRBOWDOWN,
        /* readystate */   HS_CRBOW1,
        /* atkstate */     HS_CRBOWATK2_1,
        /* holdatkstate */ HS_CRBOWATK2_1,
        /* flashstate */   HS_NULL,
        /* recoil */       0,
        /* motorspeed */   0,
        /* tics */         0,
        /* prev */         wp_goldwand,
        /* next */         wp_blaster,
        /* lookup */       1472,
        /* lookdown */     184
    },

    {
        /* description */  "blaster",
        /* ammotype */     am_blaster,
        /* priority */     5,
        /* minammo */      0,
        /* upstate */      HS_BLASTERUP,
        /* downstate */    HS_BLASTERDOWN,
        /* readystate */   HS_BLASTERREADY,
        /* atkstate */     HS_BLASTERATK2_1,
        /* holdatkstate */ HS_BLASTERATK2_3,
        /* flashstate */   HS_NULL,
        /* recoil */       0,
        /* motorspeed */   0,
        /* tics */         0,
        /* prev */         wp_crossbow,
        /* next */         wp_skullrod,
        /* lookup */       1472,
        /* lookdown */     1472
    },

    {
        /* description */  "skull rod",
        /* ammotype */     am_skullrod,
        /* priority */     6,
        /* minammo */      0,
        /* upstate */      HS_HORNRODUP,
        /* downstate */    HS_HORNRODDOWN,
        /* readystate */   HS_HORNRODREADY,
        /* atkstate */     HS_HORNRODATK2_1,
        /* holdatkstate */ HS_HORNRODATK2_1,
        /* flashstate */   HS_NULL,
        /* recoil */       0,
        /* motorspeed */   0,
        /* tics */         0,
        /* prev */         wp_blaster,
        /* next */         wp_phoenixrod,
        /* lookup */       1472,
        /* lookdown */     182
    },

    {
        /* description */  "phoenix rod",
        /* ammotype */     am_phoenixrod,
        /* priority */     7,
        /* minammo */      0,
        /* upstate */      HS_PHOENIXUP,
        /* downstate */    HS_PHOENIXDOWN,
        /* readystate */   HS_PHOENIXREADY,
        /* atkstate */     HS_PHOENIXATK2_1,
        /* holdatkstate */ HS_PHOENIXATK2_2,
        /* flashstate */   HS_NULL,
        /* recoil */       0,
        /* motorspeed */   0,
        /* tics */         0,
        /* prev */         wp_skullrod,
        /* next */         wp_mace,
        /* lookup */       1472,
        /* lookdown */     182
    },

    {
        /* description */  "mace",
        /* ammotype */     am_mace,
        /* priority */     8,
        /* minammo */      0,
        /* upstate */      HS_MACEUP,
        /* downstate */    HS_MACEDOWN,
        /* readystate */   HS_MACEREADY,
        /* atkstate */     HS_MACEATK2_1,
        /* holdatkstate */ HS_MACEATK2_1,
        /* flashstate */   HS_NULL,
        /* recoil */       0,
        /* motorspeed */   0,
        /* tics */         0,
        /* prev */         wp_phoenixrod,
        /* next */         wp_beak,
        /* lookup */       1472,
        /* lookdown */     736
    },

    {
        /* description */  "gauntlets",
        /* ammotype */     am_noammo,
        /* priority */     2,
        /* minammo */      0,
        /* upstate */      HS_GAUNTLETUP2,
        /* downstate */    HS_GAUNTLETDOWN2,
        /* readystate */   HS_GAUNTLETREADY2_1,
        /* atkstate */     HS_GAUNTLETATK2_1,
        /* holdatkstate */ HS_GAUNTLETATK2_3,
        /* flashstate */   HS_NULL,
        /* recoil */       0,
        /* motorspeed */   0,
        /* tics */         0,
        /* prev */         wp_staff,
        /* next */         wp_goldwand,
        /* lookup */       1472,
        /* lookdown */     368
    },

    {
        /* description */  "beak",
        /* ammotype */     am_noammo,
        /* priority */     0,
        /* minammo */      0,
        /* upstate */      HS_BEAKUP,
        /* downstate */    HS_BEAKDOWN,
        /* readystate */   HS_BEAKREADY,
        /* atkstate */     HS_BEAKATK2_1,
        /* holdatkstate */ HS_BEAKATK2_1,
        /* flashstate */   HS_NULL,
        /* recoil */       0,
        /* motorspeed */   0,
        /* tics */         0,
        /* prev */         wp_mace,
        /* next */         wp_staff,
        /* lookup */       1472,
        /* lookdown */     182
    }
};
