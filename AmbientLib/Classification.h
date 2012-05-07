/*
 * Classification.h
 *****************************************************************************
 * Copyright (C) 2011 - 2013 Alpen-Adria-Universit�t Klagenfurt
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


#ifndef CLASSIFICATION_H
#define CLASSIFICATION_H

#include <map>
#include <vector>
#include <string>
#include <windows.h>

class Classification
{
private:
	std::map<std::string, COLORREF> colorTable;
	std::vector<std::string> locationTable;
	std::vector<std::string> scentTable;
	std::vector<std::string> sprayingTypeTable;

public:
	Classification();
	~Classification();
	std::vector<std::string> getLocationTable();
	bool containsLocation(std::string locationURI);
	std::map<std::string, COLORREF> getColorTable();
	bool containsColor(std::string colorURI);
	COLORREF getRGBforColor(std::string colorURI);
	std::vector<std::string> getSprayingTypeTable();
	bool containsSprayingType(std::string sprayingTypeURI);
	std::vector<std::string> getScentTable();
	bool containsScent(std::string scentURI);

public:
	static const std::string COLORURIBASE;
	static const std::string COLOR_ALICE_BLUE;
	static const std::string COLOR_ALIZARIN;
	static const std::string COLOR_AMARANTH;
	static const std::string COLOR_AMARANTH_PINK;
	static const std::string COLOR_AMBER;
	static const std::string COLOR_AMETHYST;
	static const std::string COLOR_APRICOT;
	static const std::string COLOR_AQUA;
	static const std::string COLOR_AQUAMARINE;
	static const std::string COLOR_ARMY_GREEN;
	static const std::string COLOR_ASPARAGUS;
	static const std::string COLOR_ATOMIC_TANGERINE;
	static const std::string COLOR_AUBURN;
	static const std::string COLOR_AZURE_COLOR_WHEEL;
	static const std::string COLOR_AZURE_WEB;
	static const std::string COLOR_BABY_BLUE;
	static const std::string COLOR_BEIGE;
	static const std::string COLOR_BISTRE;
	static const std::string COLOR_BLACK;
	static const std::string COLOR_BLUE;
	static const std::string COLOR_BLUE_PIGMENT;
	static const std::string COLOR_BLUE_RYB;
	static const std::string COLOR_BLUE_GREEN;
	static const std::string COLOR_BLUE_VIOLET;
	static const std::string COLOR_BONDI_BLUE;
	static const std::string COLOR_BRASS;
	static const std::string COLOR_BRIGHT_GREEN;
	static const std::string COLOR_BRIGHT_PINK;
	static const std::string COLOR_BRIGHT_TURQUOISE;
	static const std::string COLOR_BRILLIANT_ROSE;
	static const std::string COLOR_BRINK_PINK;
	static const std::string COLOR_BRONZE;
	static const std::string COLOR_BROWN;
	static const std::string COLOR_BUFF;
	static const std::string COLOR_BURGUNDY;
	static const std::string COLOR_BURNT_ORANGE;
	static const std::string COLOR_BURNT_SIENNA;
	static const std::string COLOR_BURNT_UMBER;
	static const std::string COLOR_CAMOUFLAGE_GREEN;
	static const std::string COLOR_CAPUT_MORTUUM;
	static const std::string COLOR_CARDINAL;
	static const std::string COLOR_CARMINE;
	static const std::string COLOR_CARMINE_PINK;
	static const std::string COLOR_CARNATION_PINK;
	static const std::string COLOR_CAROLINA_BLUE;
	static const std::string COLOR_CARROT_ORANGE;
	static const std::string COLOR_CELADON;
	static const std::string COLOR_CERISE;
	static const std::string COLOR_CERISE_PINK;
	static const std::string COLOR_CERULEAN;
	static const std::string COLOR_CERULEAN_BLUE;
	static const std::string COLOR_CHAMPAGNE;
	static const std::string COLOR_CHARCOAL;
	static const std::string COLOR_CHARTREUSE_TRADITIONAL;
	static const std::string COLOR_CHARTREUSE_WEB;
	static const std::string COLOR_CHERRY_BLOSSOM_PINK;
	static const std::string COLOR_CHESTNUT;
	static const std::string COLOR_CHOCOLATE;
	static const std::string COLOR_CINNABAR;
	static const std::string COLOR_CINNAMON;
	static const std::string COLOR_COBALT;
	static const std::string COLOR_COLUMBIA_BLUE;
	static const std::string COLOR_COPPER;
	static const std::string COLOR_COPPER_ROSE;
	static const std::string COLOR_CORAL;
	static const std::string COLOR_CORAL_PINK;
	static const std::string COLOR_CORAL_RED;
	static const std::string COLOR_CORN;
	static const std::string COLOR_CORNFLOWER_BLUE;
	static const std::string COLOR_COSMIC_LATTE;
	static const std::string COLOR_CREAM;
	static const std::string COLOR_CRIMSON;
	static const std::string COLOR_CYAN;
	static const std::string COLOR_CYAN_PROCESS;
	static const std::string COLOR_DARK_BLUE;
	static const std::string COLOR_DARK_BROWN;
	static const std::string COLOR_DARK_CERULEAN;
	static const std::string COLOR_DARK_CHESTNUT;
	static const std::string COLOR_DARK_CORAL;
	static const std::string COLOR_DARK_GOLDENROD;
	static const std::string COLOR_DARK_GREEN;
	static const std::string COLOR_DARK_KHAKI;
	static const std::string COLOR_DARK_MAGENTA;
	static const std::string COLOR_DARK_PASTEL_GREEN;
	static const std::string COLOR_DARK_PINK;
	static const std::string COLOR_DARK_SCARLET;
	static const std::string COLOR_DARK_SALMON;
	static const std::string COLOR_DARK_SLATE_GRAY;
	static const std::string COLOR_DARK_SPRING_GREEN;
	static const std::string COLOR_DARK_TAN;
	static const std::string COLOR_DARK_TURQUOISE;
	static const std::string COLOR_DARK_VIOLET;
	static const std::string COLOR_DEEP_CARMINE_PINK;
	static const std::string COLOR_DEEP_CERISE;
	static const std::string COLOR_DEEP_CHESTNUT;
	static const std::string COLOR_DEEP_FUCHSIA;
	static const std::string COLOR_DEEP_LILAC;
	static const std::string COLOR_DEEP_MAGENTA;
	static const std::string COLOR_DEEP_PEACH;
	static const std::string COLOR_DEEP_PINK;
	static const std::string COLOR_DENIM;
	static const std::string COLOR_DODGER_BLUE;
	static const std::string COLOR_ECRU;
	static const std::string COLOR_EGYPTIAN_BLUE;
	static const std::string COLOR_ELECTRIC_BLUE;
	static const std::string COLOR_ELECTRIC_GREEN_X11_GREEN;
	static const std::string COLOR_ELECTRIC_INDIGO;
	static const std::string COLOR_ELECTRIC_LIME;
	static const std::string COLOR_ELECTRIC_PURPLE;
	static const std::string COLOR_EMERALD;
	static const std::string COLOR_EGGPLANT;
	static const std::string COLOR_FALU_RED;
	static const std::string COLOR_FERN_GREEN;
	static const std::string COLOR_FIREBRICK;
	static const std::string COLOR_FLAX;
	static const std::string COLOR_FOREST_GREEN;
	static const std::string COLOR_FRENCH_ROSE;
	static const std::string COLOR_FUCHSIA;
	static const std::string COLOR_FUCHSIA_PINK;
	static const std::string COLOR_GAMBOGE;
	static const std::string COLOR_GOLD_METALLIC;
	static const std::string COLOR_GOLD_WEB_GOLDEN;
	static const std::string COLOR_GOLDEN_BROWN;
	static const std::string COLOR_GOLDEN_YELLOW;
	static const std::string COLOR_GOLDENROD;
	static const std::string COLOR_GREY_ASPARAGUS;
	static const std::string COLOR_GREEN_COLOR_WHEEL_X11_GREEN;
	static const std::string COLOR_GREEN_HTMLCSS_GREEN;
	static const std::string COLOR_GREEN_PIGMENT;
	static const std::string COLOR_GREEN_RYB;
	static const std::string COLOR_GREEN_YELLOW;
	static const std::string COLOR_GREY;
	static const std::string COLOR_HAN_PURPLE;
	static const std::string COLOR_HARLEQUIN;
	static const std::string COLOR_HELIOTROPE;
	static const std::string COLOR_HOLLYWOOD_CERISE;
	static const std::string COLOR_HOT_MAGENTA;
	static const std::string COLOR_HOT_PINK;
	static const std::string COLOR_INDIGO_DYE;
	static const std::string COLOR_INDIGO_WEB;
	static const std::string COLOR_INTERNATIONAL_KLEIN_BLUE;
	static const std::string COLOR_INTERNATIONAL_ORANGE;
	static const std::string COLOR_ISLAMIC_GREEN;
	static const std::string COLOR_IVORY;
	static const std::string COLOR_JADE;
	static const std::string COLOR_KELLY_GREEN;
	static const std::string COLOR_KHAKI;
	static const std::string COLOR_KHAKI_X11_LIGHT_KHAKI;
	static const std::string COLOR_LAVENDER_FLORAL;
	static const std::string COLOR_LAVENDER_WEB;
	static const std::string COLOR_LAVENDER_BLUE;
	static const std::string COLOR_LAVENDER_BLUSH;
	static const std::string COLOR_LAVENDER_GREY;
	static const std::string COLOR_LAVENDER_MAGENTA;
	static const std::string COLOR_LAVENDER_PINK;
	static const std::string COLOR_LAVENDER_PURPLE;
	static const std::string COLOR_LAVENDER_ROSE;
	static const std::string COLOR_LAWN_GREEN;
	static const std::string COLOR_LEMON;
	static const std::string COLOR_LEMON_CHIFFON;
	static const std::string COLOR_LIGHT_BLUE;
	static const std::string COLOR_LIGHT_PINK;
	static const std::string COLOR_LILAC;
	static const std::string COLOR_LIME_COLOR_WHEEL;
	static const std::string COLOR_LIME_WEB_X11_GREEN;
	static const std::string COLOR_LIME_GREEN;
	static const std::string COLOR_LINEN;
	static const std::string COLOR_MAGENTA;
	static const std::string COLOR_MAGENTA_DYE;
	static const std::string COLOR_MAGENTA_PROCESS;
	static const std::string COLOR_MAGIC_MINT;
	static const std::string COLOR_MAGNOLIA;
	static const std::string COLOR_MALACHITE;
	static const std::string COLOR_MAROON_HTMLCSS;
	static const std::string COLOR_MAROON_X11;
	static const std::string COLOR_MAYA_BLUE;
	static const std::string COLOR_MAUVE;
	static const std::string COLOR_MAUVE_TAUPE;
	static const std::string COLOR_MEDIUM_BLUE;
	static const std::string COLOR_MEDIUM_CARMINE;
	static const std::string COLOR_MEDIUM_LAVENDER_MAGENTA;
	static const std::string COLOR_MEDIUM_PURPLE;
	static const std::string COLOR_MEDIUM_SPRING_GREEN;
	static const std::string COLOR_MIDNIGHT_BLUE;
	static const std::string COLOR_MIDNIGHT_GREEN_EAGLE_GREEN;
	static const std::string COLOR_MINT_GREEN;
	static const std::string COLOR_MISTY_ROSE;
	static const std::string COLOR_MOSS_GREEN;
	static const std::string COLOR_MOUNTBATTEN_PINK;
	static const std::string COLOR_MUSTARD;
	static const std::string COLOR_MYRTLE;
	static const std::string COLOR_NAVAJO_WHITE;
	static const std::string COLOR_NAVY_BLUE;
	static const std::string COLOR_OCHRE;
	static const std::string COLOR_OFFICE_GREEN;
	static const std::string COLOR_OLD_GOLD;
	static const std::string COLOR_OLD_LACE;
	static const std::string COLOR_OLD_LAVENDER;
	static const std::string COLOR_OLD_ROSE;
	static const std::string COLOR_OLIVE;
	static const std::string COLOR_OLIVE_DRAB;
	static const std::string COLOR_OLIVINE;
	static const std::string COLOR_ORANGE_COLOR_WHEEL;
	static const std::string COLOR_ORANGE_RYB;
	static const std::string COLOR_ORANGE_WEB;
	static const std::string COLOR_ORANGE_PEEL;
	static const std::string COLOR_ORANGE_RED;
	static const std::string COLOR_ORCHID;
	static const std::string COLOR_PALE_BLUE;
	static const std::string COLOR_PALE_BROWN;
	static const std::string COLOR_PALE_CARMINE;
	static const std::string COLOR_PALE_CHESTNUT;
	static const std::string COLOR_PALE_CORNFLOWER_BLUE;
	static const std::string COLOR_PALE_MAGENTA;
	static const std::string COLOR_PALE_PINK;
	static const std::string COLOR_PALE_RED_VIOLET;
	static const std::string COLOR_PAPAYA_WHIP;
	static const std::string COLOR_PASTEL_GREEN;
	static const std::string COLOR_PASTEL_PINK;
	static const std::string COLOR_PEACH;
	static const std::string COLOR_PEACH_ORANGE;
	static const std::string COLOR_PEACH_YELLOW;
	static const std::string COLOR_PEAR;
	static const std::string COLOR_PERIWINKLE;
	static const std::string COLOR_PERSIAN_BLUE;
	static const std::string COLOR_PERSIAN_GREEN;
	static const std::string COLOR_PERSIAN_INDIGO;
	static const std::string COLOR_PERSIAN_ORANGE;
	static const std::string COLOR_PERSIAN_RED;
	static const std::string COLOR_PERSIAN_PINK;
	static const std::string COLOR_PERSIAN_ROSE;
	static const std::string COLOR_PERSIMMON;
	static const std::string COLOR_PINE_GREEN;
	static const std::string COLOR_PINK;
	static const std::string COLOR_PINK_ORANGE;
	static const std::string COLOR_PLATINUM;
	static const std::string COLOR_PLUM_WEB;
	static const std::string COLOR_POWDER_BLUE_WEB;
	static const std::string COLOR_PUCE;
	static const std::string COLOR_PRUSSIAN_BLUE;
	static const std::string COLOR_PSYCHEDELIC_PURPLE;
	static const std::string COLOR_PUMPKIN;
	static const std::string COLOR_PURPLE_HTMLCSS;
	static const std::string COLOR_PURPLE_X11;
	static const std::string COLOR_PURPLE_TAUPE;
	static const std::string COLOR_RAW_UMBER;
	static const std::string COLOR_RAZZMATAZZ;
	static const std::string COLOR_RED;
	static const std::string COLOR_RED_PIGMENT;
	static const std::string COLOR_RED_RYB;
	static const std::string COLOR_RED_VIOLET;
	static const std::string COLOR_RICH_CARMINE;
	static const std::string COLOR_ROBIN_EGG_BLUE;
	static const std::string COLOR_ROSE;
	static const std::string COLOR_ROSE_MADDER;
	static const std::string COLOR_ROSE_TAUPE;
	static const std::string COLOR_ROYAL_BLUE;
	static const std::string COLOR_ROYAL_PURPLE;
	static const std::string COLOR_RUBY;
	static const std::string COLOR_RUSSET;
	static const std::string COLOR_RUST;
	static const std::string COLOR_SAFETY_ORANGE_BLAZE_ORANGE;
	static const std::string COLOR_SAFFRON;
	static const std::string COLOR_SALMON;
	static const std::string COLOR_SANDY_BROWN;
	static const std::string COLOR_SANGRIA;
	static const std::string COLOR_SAPPHIRE;
	static const std::string COLOR_SCARLET;
	static const std::string COLOR_SCHOOL_BUS_YELLOW;
	static const std::string COLOR_SEA_GREEN;
	static const std::string COLOR_SEASHELL;
	static const std::string COLOR_SELECTIVE_YELLOW;
	static const std::string COLOR_SEPIA;
	static const std::string COLOR_SHAMROCK_GREEN;
	static const std::string COLOR_SHOCKING_PINK;
	static const std::string COLOR_SILVER;
	static const std::string COLOR_SKY_BLUE;
	static const std::string COLOR_SLATE_GREY;
	static const std::string COLOR_SMALT_DARK_POWDER_BLUE;
	static const std::string COLOR_SPRING_BUD;
	static const std::string COLOR_SPRING_GREEN;
	static const std::string COLOR_STEEL_BLUE;
	static const std::string COLOR_TAN;
	static const std::string COLOR_TANGERINE;
	static const std::string COLOR_TANGERINE_YELLOW;
	static const std::string COLOR_TAUPE;
	static const std::string COLOR_TEA_GREEN;
	static const std::string COLOR_TEA_ROSE_ORANGE;
	static const std::string COLOR_TEA_ROSE_ROSE;
	static const std::string COLOR_TEAL;
	static const std::string COLOR_TENNY_TAWNY;
	static const std::string COLOR_TERRA_COTTA;
	static const std::string COLOR_THISTLE;
	static const std::string COLOR_TOMATO;
	static const std::string COLOR_TURQUOISE;
	static const std::string COLOR_TYRIAN_PURPLE;
	static const std::string COLOR_ULTRAMARINE;
	static const std::string COLOR_ULTRA_PINK;
	static const std::string COLOR_UNITED_NATIONS_BLUE;
	static const std::string COLOR_VEGAS_GOLD;
	static const std::string COLOR_VERMILION;
	static const std::string COLOR_VIOLET;
	static const std::string COLOR_VIOLET_WEB;
	static const std::string COLOR_VIOLET_RYB;
	static const std::string COLOR_VIRIDIAN;
	static const std::string COLOR_WHEAT;
	static const std::string COLOR_WHITE;
	static const std::string COLOR_WISTERIA;
	static const std::string COLOR_YELLOW;
	static const std::string COLOR_YELLOW_PROCESS;
	static const std::string COLOR_YELLOW_RYB;
	static const std::string COLOR_YELLOW_GREEN;

		// LocationCS
	static const std::string LOCATIONURIBASE;
	static const std::string LOC_X_LEFT;
	static const std::string LOC_X_CENTERLEFT;
	static const std::string LOC_X_CENTER;
	static const std::string LOC_X_CENTERRIGHT;
	static const std::string LOC_X_RIGHT;
	static const std::string LOC_Y_BOTTOM;
	static const std::string LOC_Y_MIDDLE;
	static const std::string LOC_Y_TOP;
	static const std::string LOC_Z_BACK;
	static const std::string LOC_Z_MIDWAY;
	static const std::string LOC_Z_FRONT;
	static const std::string LOC_EVERYWHERE;

	// A.2.3	ScentCS
	static const std::string SCENTURIBASE;
	static const std::string SCENT_ROSE;
	static const std::string SCENT_ACACIA;
	static const std::string SCENT_CHRYSANTHEMUM;
	static const std::string SCENT_LILAC;
	static const std::string SCENT_MINT;
	static const std::string SCENT_JASMINE;
	static const std::string SCENT_PINETREE;
	static const std::string SCENT_ORANGE;
	static const std::string SCENT_GRAPE;
	static const std::string SCENT_ALMONDS;
	static const std::string SCENT_AMARETTO;
	static const std::string SCENT_APPLES_GREEN;
	static const std::string SCENT_APPLES_RED;
	static const std::string SCENT_BACON;
	static const std::string SCENT_BACON_SMOKEY;
	static const std::string SCENT_BANANA;
	static const std::string SCENT_BANANA_SPLITS;
	static const std::string SCENT_BASIL_HERD;
	static const std::string SCENT_BEEF;
	static const std::string SCENT_BLACKCURRANT;
	static const std::string SCENT_BOILED_CABBAGE;
	static const std::string SCENT_BRANDY;
	static const std::string SCENT_BREAD;
	static const std::string SCENT_BUBBLE_GUM;
	static const std::string SCENT_CAKE_SHOP;
	static const std::string SCENT_CANDY_FLOSS;
	static const std::string SCENT_CARAMEL_TOFFEE;
	static const std::string SCENT_CARROT;
	static const std::string SCENT_CELERY;
	static const std::string SCENT_CHERRY;
	static const std::string SCENT_CHICKEN;
	static const std::string SCENT_COCONUT;
	static const std::string SCENT_CHOCOLATE_DARK;
	static const std::string SCENT_CHOCOLATE_ORANGE;
	static const std::string SCENT_CHRISTMAS_APPLE;
	static const std::string SCENT_CHRISTMAS_PUDDING;
	static const std::string SCENT_CINNAMON;
	static const std::string SCENT_COFFEE_CHOCOLATE;
	static const std::string SCENT_COFFEE_CREAM;
	static const std::string SCENT_COLA;
	static const std::string SCENT_CONFECTIONARY;
	static const std::string SCENT_COOKIE;
	static const std::string SCENT_CORIANDER;
	static const std::string SCENT_CRUSTY_BREAD;
	static const std::string SCENT_CURRY;
	static const std::string SCENT_FISHMARKET;
	static const std::string SCENT_FRUIT_CAKE;
	static const std::string SCENT_FRUIT_PUNCH_BR_FRUITY_SWEETS;
	static const std::string SCENT_GARDEN_MINT;
	static const std::string SCENT_GARLIC;
	static const std::string SCENT_GINGERBREAD;
	static const std::string SCENT_GRANNIES_KITCHEN;
	static const std::string SCENT_GRAPEFRUIT;
	static const std::string SCENT_HERBS_MIXED;
	static const std::string SCENT_HERRING;
	static const std::string SCENT_HONEY;
	static const std::string SCENT_HOT_APPLE_PIE;
	static const std::string SCENT_IRISH_CREAM;
	static const std::string SCENT_JAMBALAYA;
	static const std::string SCENT_JELLY_BABIES;
	static const std::string SCENT_KIWI_FRUIT;
	static const std::string SCENT_LIME_SPLASH;
	static const std::string SCENT_LIQUORICE;
	static const std::string SCENT_MANGO_DELIGHT;
	static const std::string SCENT_MELON;
	static const std::string SCENT_MINT_CHOCOLATE;
	static const std::string SCENT_MULLED_WINE;
	static const std::string SCENT_NUTMEG;
	static const std::string SCENT_ONION;
	static const std::string SCENT_ORANGE_CUPCAKE;
	static const std::string SCENT_ORANGE_NF;
	static const std::string SCENT_PASSION_FRUIT;
	static const std::string SCENT_PEACH_FLESH;
	static const std::string SCENT_PEAR_DROPS;
	static const std::string SCENT_PEPPERMINT;
	static const std::string SCENT_PINA_COLADA;
	static const std::string SCENT_PINEAPPLE;
	static const std::string SCENT_POPCORN;
	static const std::string SCENT_RASPBERRY;
	static const std::string SCENT_RASPBERRY_RIPPLES;
	static const std::string SCENT_RHUBARB;
	static const std::string SCENT_ROSEMARY;
	static const std::string SCENT_RUM;
	static const std::string SCENT_SMOKED_FISH;
	static const std::string SCENT_SPICES_MIXED;
	static const std::string SCENT_STIR_FRY;
	static const std::string SCENT_STRAWBERRY;
	static const std::string SCENT_SUGAR_SPICE_CHRISTMAS_AROMA;
	static const std::string SCENT_SWEET_SHERRY;
	static const std::string SCENT_TANGERINE;
	static const std::string SCENT_TEA_LEAF;
	static const std::string SCENT_THAI_CURRY;
	static const std::string SCENT_TOFFEE_APPLE;
	static const std::string SCENT_TOMATO_PLANT;
	static const std::string SCENT_WATERMELON;
	static const std::string SCENT_WHISKY;
	static const std::string SCENT_WINE_OAK_CASK;
	static const std::string SCENT_VANILLA;
	static const std::string SCENT_WHISKY_SCOTCH;
	static const std::string SCENT_ALPINE_LAUNDRY_POWDER;
	static const std::string SCENT_ALPINE;
	static const std::string SCENT_AMULET;
	static const std::string SCENT_AQUAWAVE;
	static const std::string SCENT_ARISTOCRAT;
	static const std::string SCENT_BABY_POWDER;
	static const std::string SCENT_BEAUTY_SOAP;
	static const std::string SCENT_BERGAMOT;
	static const std::string SCENT_BOILER_ROOM;
	static const std::string SCENT_BOUQUET;
	static const std::string SCENT_BREWERY;
	static const std::string SCENT_BURNING_PEAT;
	static const std::string SCENT_BURNT_WOOD;
	static const std::string SCENT_CANNON;
	static const std::string SCENT_CARNATION;
	static const std::string SCENT_CARIBBEAN_HOLIDAY;
	static const std::string SCENT_CARBOLIC_SOAP;
	static const std::string SCENT_CEDAR_WOOD;
	static const std::string SCENT_CHAMOMILE;
	static const std::string SCENT_CHRISTMAS_BERRIES;
	static const std::string SCENT_CHRISTMAS_TREE;
	static const std::string SCENT_CHRISTMAS_TIME;
	static const std::string SCENT_CHURCH_INCENSE;
	static const std::string SCENT_CLOISTERS;
	static const std::string SCENT_CLINIC_HOSPITAL;
	static const std::string SCENT_COAL_FACE;
	static const std::string SCENT_COAL_FIRE;
	static const std::string SCENT_COAL_GAS;
	static const std::string SCENT_COCOMANGO;
	static const std::string SCENT_CUBAN_CIGAR_SMOKE;
	static const std::string SCENT_CUT_GRASS;
	static const std::string SCENT_DEEP_HEAT;
	static const std::string SCENT_DENTIST_CLOVE_OIL;
	static const std::string SCENT_DINOSAUR;
	static const std::string SCENT_DIRTY_LINEN;
	static const std::string SCENT_DRAGONS_BREATH;
	static const std::string SCENT_DRESSING_ROOM_FOOTBALL;
	static const std::string SCENT_EARTHY;
	static const std::string SCENT_EAU_DE_COLOGNE;
	static const std::string SCENT_EUCALYPTUS;
	static const std::string SCENT_EAU_DE_COLOGNE_FACTORY;
	static const std::string SCENT_FARMYARD;
	static const std::string SCENT_FACTORY;
	static const std::string SCENT_FISH_MARKET;
	static const std::string SCENT_FLATULENCE;
	static const std::string SCENT_FOOTIE_PITCH;
	static const std::string SCENT_FOREST;
	static const std::string SCENT_FOX;
	static const std::string SCENT_FREESIA;
	static const std::string SCENT_FRESH_AIR;
	static const std::string SCENT_FROSTY;
	static const std::string SCENT_GOLDEN_ONE;
	static const std::string SCENT_GRASS_HAY;
	static const std::string SCENT_GUN_SMOKE;
	static const std::string SCENT_HAVANA_CIGAR;
	static const std::string SCENT_HAWAIIAN;
	static const std::string SCENT_HEATHER_BRACKEN;
	static const std::string SCENT_HONEYSUCKLE;
	static const std::string SCENT_HOSPITAL_MODERN_DAY;
	static const std::string SCENT_HYACINTH;
	static const std::string SCENT_INCENSE;
	static const std::string SCENT_IRON_SMELTING;
	static const std::string SCENT_JAGUAR_SPRAY;
	static const std::string SCENT_JAPANESE_POW;
	static const std::string SCENT_LAVENDER;
	static const std::string SCENT_LEATHER_CREAM;
	static const std::string SCENT_LEATHER_HIDE;
	static const std::string SCENT_LEMON_EUCALYPTUS_MINT;
	static const std::string SCENT_MACHINE_OIL;
	static const std::string SCENT_MAHOGANY;
	static const std::string SCENT_MAN_O_WAR;
	static const std::string SCENT_MANURE_BR_METHANE;
	static const std::string SCENT_MODERN_DAY_HOSPITAL;
	static const std::string SCENT_MOUNTAIN_HEATHER;
	static const std::string SCENT_MUMMY_EGYPTIAN;
	static const std::string SCENT_MUSTY;
	static const std::string SCENT_OAK;
	static const std::string SCENT_OLD_DRIFTER_SHIP;
	static const std::string SCENT_OLD_INN;
	static const std::string SCENT_OLD_RIVER;
	static const std::string SCENT_OLD_SMITHY;
	static const std::string SCENT_OUT_AT_SEA;
	static const std::string SCENT_OZONE;
	static const std::string SCENT_PEAT;
	static const std::string SCENT_PENCIL_WOOD_SHAVINGS;
	static const std::string SCENT_PEONY;
	static const std::string SCENT_PHOSGENE_GAS;
	static const std::string SCENT_PINE;
	static const std::string SCENT_PINEAPPLE_PLANTATION;
	static const std::string SCENT_PINE_HEATHER_PEAT;
	static const std::string SCENT_PIT_PONIES;
	static const std::string SCENT_POLISH_WAX;
	static const std::string SCENT_POT_POURRI;
	static const std::string SCENT_RIVERBANK;
	static const std::string SCENT_RIVER_TROPICS;
	static const std::string SCENT_ROPE_TAR;
	static const std::string SCENT_ROSEWOOD;
	static const std::string SCENT_RUBBISH_ACRID;
	static const std::string SCENT_SANDALWOOD;
	static const std::string SCENT_SANDALWOOD_BASIL;
	static const std::string SCENT_SEA_BREEZE;
	static const std::string SCENT_SEA_SHORE;
	static const std::string SCENT_SHEBA;
	static const std::string SCENT_SHIPS_CANNON;
	static const std::string SCENT_SNOWDROP;
	static const std::string SCENT_SPORTS_CHANGING_ROOM;
	static const std::string SCENT_STABLES_HORSES;
	static const std::string SCENT_STARS_DRESSING_ROOM;
	static const std::string SCENT_STEAM_OIL_SHIPS;
	static const std::string SCENT_STEAM_OIL_TRAINS;
	static const std::string SCENT_STREET_1930S;
	static const std::string SCENT_STREET_BOMB;
	static const std::string SCENT_SUN_SAND_COCONUT;
	static const std::string SCENT_SWAMP;
	static const std::string SCENT_SWEATY_FEET;
	static const std::string SCENT_SWEET_PEAS;
	static const std::string SCENT_TOBACCO_LEAF;
	static const std::string SCENT_TRAIN_SMOKE;
	static const std::string SCENT_TROPHY_ROOM;
	static const std::string SCENT_TROPICAL;
	static const std::string SCENT_TROPICAL_RAIN_FOREST;
	static const std::string SCENT_UNISEX_PERFUME;
	static const std::string SCENT_URINE;
	static const std::string SCENT_USA_SWAMP;
	static const std::string SCENT_VICTORIAN_LAVENDER;
	static const std::string SCENT_VIOLETS;
	static const std::string SCENT_VOLCANO;
	static const std::string SCENT_VOMIT;
	static const std::string SCENT_WALLFLOWER;
	static const std::string SCENT_WASHDAY;
	static const std::string SCENT_WILD_STAG;
	static const std::string SCENT_WINE_CASK_OAK;
	static const std::string SCENT_WISTERIA;
	static const std::string SCENT_WOODSMOKE;
	static const std::string SCENT_YLANG_JASMIN_MYRRH;
	static const std::string SCENT_YULETIDE;
	static const std::string SCENT_AFRICAN_RAIN;
	static const std::string SCENT_ALLEGRIA;
	static const std::string SCENT_AMBER;
	static const std::string SCENT_APPLE_GREEN;
	static const std::string SCENT_ASAFOETIDA;
	static const std::string SCENT_AUTUMN_FIELDS;
	static const std::string SCENT_AUTUMN_HARVEST;
	static const std::string SCENT_BALSAM_FIR;
	static const std::string SCENT_BALSAM_FIR_NEEDLE;
	static const std::string SCENT_BARNYARD;
	static const std::string SCENT_BEER;
	static const std::string SCENT_BENZOIN;
	static const std::string SCENT_BIRCH_TAR;
	static const std::string SCENT_BIRTHDAY_CAKE;
	static const std::string SCENT_BLUEBERRY_COBBLER;
	static const std::string SCENT_BOUQUET_OF_ROSES;
	static const std::string SCENT_BUCHU;
	static const std::string SCENT_BURNING_RUBBER;
	static const std::string SCENT_CACTUS_FLOWER;
	static const std::string SCENT_CADE;
	static const std::string SCENT_CAMPFIRE;
	static const std::string SCENT_CAMPFIRE_SMOKE;
	static const std::string SCENT_CAMPHOR;
	static const std::string SCENT_CARIBBEAN_NIGHT;
	static const std::string SCENT_CEDAR;
	static const std::string SCENT_CHAMPAGNE_STRAWBERRIES;
	static const std::string SCENT_CHANEL_NO5_TYPE;
	static const std::string SCENT_CHOCOLATE;
	static const std::string SCENT_CHRISTMAS_COOKIES;
	static const std::string SCENT_CLEAN_COTTON;
	static const std::string SCENT_COTTON_CANDY;
	static const std::string SCENT_CREME_BRULE;
	static const std::string SCENT_CYPRESS_GROVE;
	static const std::string SCENT_DUMPSTER;
	static const std::string SCENT_DUNG;
	static const std::string SCENT_EASTER_LILLIES;
	static const std::string SCENT_EGG_NOG_2;
	static const std::string SCENT_EUCALYPTUS_DIVES;
	static const std::string SCENT_EVERGREEN;
	static const std::string SCENT_EXHAUST;
	static const std::string SCENT_FISH;
	static const std::string SCENT_FOREST_RAIN;
	static const std::string SCENT_FORGET_ME_NOT;
	static const std::string SCENT_FRANGIPANI;
	static const std::string SCENT_FRENCH_FRIES;
	static const std::string SCENT_FRESH_BREAD;
	static const std::string SCENT_FRESH_CUT_GRASS;
	static const std::string SCENT_FRESH_LAUNDRY;
	static const std::string SCENT_FRYING_BACON;
	static const std::string SCENT_FUDGE_BROWNIE;
	static const std::string SCENT_GARDENIA;
	static const std::string SCENT_GRANDMAS_ATTIC;
	static const std::string SCENT_HALLOWEEN_GREASEPAINT;
	static const std::string SCENT_HAWAIAN_TREAT;
	static const std::string SCENT_INDIAN_SUMMER;
	static const std::string SCENT_JET_FUEL;
	static const std::string SCENT_JUNIPER_BERRY;
	static const std::string SCENT_LEATHER;
	static const std::string SCENT_LOTUS;
	static const std::string SCENT_MANGO_MANDARIN;
	static const std::string SCENT_MAPLE_SYRUP;
	static const std::string SCENT_MILDEW;
	static const std::string SCENT_MOTHER_EARTH;
	static const std::string SCENT_MUSK;
	static const std::string SCENT_NEW_MOWN_GRASS_2;
	static const std::string SCENT_NEW_MOWN_GRASS_3;
	static const std::string SCENT_OAK_MOSS;
	static const std::string SCENT_OPEN_FIREPLACE;
	static const std::string SCENT_PALMAROSA;
	static const std::string SCENT_PANCAKES_AND_MAPLE_SYRUP;
	static const std::string SCENT_PATCHOULI;
	static const std::string SCENT_PECAN_PIE;
	static const std::string SCENT_RAIN_FOREST;
	static const std::string SCENT_RICH_POTTING_SOIL;
	static const std::string SCENT_ROASTED_CHICKEN;
	static const std::string SCENT_SAGE_DALMATIAN;
	static const std::string SCENT_SEAWEED;
	static const std::string SCENT_SPANISH_MOSS;
	static const std::string SCENT_SPRING_BOUQUET;
	static const std::string SCENT_SUNTAN;
	static const std::string SCENT_THYME_BORNEOL;
	static const std::string SCENT_TOMATO_VINE;
	static const std::string SCENT_TUBEROSE;
	static const std::string SCENT_VIOLET;
	static const std::string SCENT_WARMING_GINGER;
	static const std::string SCENT_YLANG_YLANG;

	// A.2.6 SprayingTypeCS
	static const std::string SPRAYINGTYPEURIBASE;
	static const std::string SPRAYINGTYPE_WATER;
};

#endif