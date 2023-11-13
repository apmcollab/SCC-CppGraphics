#include <string>

#ifndef HersheyFont_
#define HersheyFont_


/*
#############################################################################
#
# Copyright  2023- Chris Anderson
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the Lesser GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# For a copy of the GNU General Public License see
# <http://www.gnu.org/licenses/>.
#
#############################################################################
*/

/*

 Supported fonts and their font index and name

 Font Index : 0   HersheySerif
 Font Index : 1   HersheySerif-Italic
 Font Index : 2   HersheySerif-Bold
 Font Index : 3   HersheySerif-BoldItalic
 Font Index : 4   HersheyCyrillic
 Font Index : 5   HersheyCyrillic-Oblique
 Font Index : 6   HersheySans
 Font Index : 7   HersheySans-Oblique
 Font Index : 8   HersheySans-Bold
 Font Index : 9   HersheySans-BoldOblique
 Font Index : 10  HersheyScript
 Font Index : 11  HersheyScript-Bold
 Font Index : 12  HersheyGothicEnglish
 Font Index : 13  HersheyGothicGerman
 Font Index : 14  HersheyGothicItalian
 Font Index : 15  HersheySerifSymbol
 Font Index : 16  HersheySerifSymbol-Oblique
 Font Index : 17  HersheySerifSymbol-Bold
 Font Index : 18  HersheySerifSymbol-BoldObl
 Font Index : 19  HersheySansSymbol
 Font Index : 20  HersheySansSymbol-Oblique
*/

struct HersheyFontInfoStruct
{
  std::string name;	    	/* font name */
  std::string othername;	/* an alias (for backward compatibility) */
  std::string orig_name;	/* Allen Hershey's original name for it */
  int chars[256];		    /* array of vector glyphs */
  int typeface_index;		/* default typeface for the font */
  int font_index;		    /* which font within typeface this is */
  bool obliquing;		    /* whether to apply obliquing */
  bool iso8859_1;		    /* whether font encoding is iso8859-1 */
  bool visible;			    /* whether font is visible, i.e. not internal*/
};

class HersheyFont
{
    public :
    
    HersheyFont();
    HersheyFont(const HersheyFont& H);
    ~HersheyFont();

    void  setFont(const std::string& fontName);
    void  setFont(int fontIndex);
    std::string getFontName();

    double getHersheyHeight();
    double getHersheyWidth(const std::string& textString);

    char* const getGlyphCodeString(char c);

    int        fontIndex;
    static int defaultFontIndex;
//
//  Hershey Font Information structures
//
    static const char* const                  OccidentalHersheyGlyphs[];
    static const struct HersheyFontInfoStruct HersheyFontInfo[];

    static double HERSHEY_BASELINE;	    /* relative to centerline */
    static double HERSHEY_CAPLINE;	    /* relative to centerline */
    static double HERSHEY_TOPLINE;	    /* relative to centerline */
    static double HERSHEY_BOTTOMLINE;   /* relative to centerline */

    static double HERSHEY_CAPHEIGHT;   /* i.e. capline - baseline    */
    static double HERSHEY_ASCENT;      /* i.e. topline - baseline    */
    static double HERSHEY_DESCENT;	   /* i.e. baseline - bottomline */
    static double HERSHEY_HEIGHT;
    static double HERSHEY_EM; 
};

#endif
