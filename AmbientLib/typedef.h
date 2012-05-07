/*
 * typedef.h
 *****************************************************************************
 * Copyright (C) 2011 - 2013 Alpen-Adria-Universitšt Klagenfurt
 *
 * Created on: April 9, 2011
 * Authors: Benjamin Rainer <benjamin.rainer@itec.aau.at>
 *
 * This file is part of ambientLib.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifndef TYPEDEF_H
#define TYPEDEF_H

static const char* LIBXML_SEM = "SEM";
static const char* LIBXML_EFFECT = "Effect";
static const char* LIBXML_GOE = "GroupOfEffects";
static const char* LIBXML_PTS = "pts";
static const char* LIBXML_TIMESCALE = "timeScale";
static const char* LIBXML_ANCHORELEMENT = "anchorElement";
static const char* LIBXML_TYPE = "type";

static const char* LIBXML_WINDTYPE = "WindType";
static const char* LIBXML_VIBRATIONTYPE = "VibrationType";
static const char* LIBXML_LIGHTTYPE = "LightType";
static const char* LIBXML_WATERSPRAYERTYPE = "SprayingType";
static const char* LIBXML_TEMPERATURETYPE = "TemperatureType";
static const char* LIBXML_SCENTTYPE = "ScentType";
static const char* LIBXML_FOGTYPE = "FogType";


static const int TYPE_NONE = 0;
static const int TYPE_VIBRATOR = 1;
static const int TYPE_WATERSPRAYER = 2;
static const int TYPE_AIRCONDITIONER = 3;
static const int TYPE_FAN = 4;
static const int TYPE_PERFUMER = 5;
static const int TYPE_LIGHT = 6;
static const int TYPE_FOG = 7;

static const char* ATT_GEN_ACTIVATE = "activate";
static const char* ATT_GEN_ALT = "alt";
static const char* ATT_GEN_DURATION = "duration";
static const char* ATT_GEN_LOCATION = "location";
static const char* ATT_GEN_FADE = "fade";
static const char* ATT_GEN_PRIORITY = "priority";
static const char* ATT_GEN_AUTOEXTRACTION = "autoExtraction";


static const char* SEMP_TRUE = "true";
static const char* SEMP_FALSE = "false";

static const char* VISUAL = "visual";
static const char* AUDIO = "audio";
static const char* BOTH = "both";

static const char* ATT_LIGHT_COLOR = "color";

static const char* ATT_INTENSITYVALUE = "intensity-value";
static const char* ATT_INTENSITYRANGE = "intensity-range";

static const int SELECTOR_LEFT_LIGHT = 0;
static const int SELECTOR_MIDDLE_LIGHT = 1;
static const int SELECTOR_RIGHT_LIGHT = 2;


#endif
