// -*- C++ -*-
/* Copyright (C) 2002, 2003
   Free Software Foundation, Inc.
     Written by Werner Lemberg <wl@gnu.org>

This file is part of groff.

groff is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2, or (at your option) any later
version.

groff is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with groff; see the file COPYING.  If not, write to the Free Software
Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. */

#include "lib.h"
#include "stringclass.h"
#include "ptable.h"

#include "unicode.h"

struct unicode_to_glyph {
  char *value;
};

declare_ptable(unicode_to_glyph)
implement_ptable(unicode_to_glyph)

PTABLE(unicode_to_glyph) unicode_to_glyph_table;

struct {
  const char *key;
  const char *value;
} unicode_to_glyph_list[] = {
  { "0021", "!" },
//{ "0022", "\"" },
  { "0022", "dq" },
//{ "0023", "#" },
  { "0023", "sh" },
//{ "0024", "$" },
  { "0024", "Do" },
  { "0025", "%" },
  { "0026", "&" },
  { "0027", "aq" },
  { "0028", "(" },
  { "0029", ")" },
  { "002A", "*" },
//{ "002B", "+" },
  { "002B", "pl" },
  { "002C", "," },
  { "002E", "." },
//{ "002F", "/" },
  { "002F", "sl" },
  { "0030", "0" },
  { "0031", "1" },
  { "0032", "2" },
  { "0033", "3" },
  { "0034", "4" },
  { "0035", "5" },
  { "0036", "6" },
  { "0037", "7" },
  { "0038", "8" },
  { "0039", "9" },
  { "003A", ":" },
  { "003B", ";" },
  { "003C", "<" },
//{ "003D", "=" },
  { "003D", "eq" },
  { "003D_0338", "!=" },
  { "003E", ">" },
  { "003F", "?" },
//{ "0040", "@" },
  { "0040", "at" },
  { "0041", "A" },
  { "0041_0300", "`A" },
  { "0041_0301", "'A" },
  { "0041_0302", "^A" },
  { "0041_0303", "~A" },
  { "0041_0308", ":A" },
  { "0041_030A", "oA" },
  { "0042", "B" },
  { "0043", "C" },
  { "0043_0301", "'C" },
  { "0043_0327", ",C" },
  { "0044", "D" },
  { "0045", "E" },
  { "0045_0300", "`E" },
  { "0045_0301", "'E" },
  { "0045_0302", "^E" },
  { "0045_0308", ":E" },
  { "0046", "F" },
  { "0047", "G" },
  { "0048", "H" },
  { "0049", "I" },
  { "0049_0300", "`I" },
  { "0049_0301", "'I" },
  { "0049_0302", "^I" },
  { "0049_0308", ":I" },
  { "004A", "J" },
  { "004B", "K" },
  { "004C", "L" },
  { "004D", "M" },
  { "004E", "N" },
  { "004E_0303", "~N" },
  { "004F", "O" },
  { "004F_0300", "`O" },
  { "004F_0301", "'O" },
  { "004F_0302", "^O" },
  { "004F_0303", "~O" },
  { "004F_0308", ":O" },
  { "0050", "P" },
  { "0051", "Q" },
  { "0052", "R" },
  { "0053", "S" },
  { "0053_030C", "vS" },
  { "0054", "T" },
  { "0055", "U" },
  { "0055_0300", "`U" },
  { "0055_0301", "'U" },
  { "0055_0302", "^U" },
  { "0055_0308", ":U" },
  { "0056", "V" },
  { "0057", "W" },
  { "0058", "X" },
  { "0059", "Y" },
  { "0059_0301", "'Y" },
  { "0059_0308", ":Y" },
  { "005A", "Z" },
  { "005A_030C", "vZ" },
  { "005B", "lB" },
//{ "005B", "[" },
  { "005C", "rs" },
//{ "005C", "\\" },
  { "005D", "rB" },
//{ "005D", "]" },
//{ "005E", "^" },
//{ "005E", "a^" },
  { "005E", "ha" },
//{ "005F", "_" },
//{ "005F", "ru" },
  { "005F", "ul" },
  { "0060", "ga" },
//{ "0060", "\\`" },
  { "0061", "a" },
  { "0061_0300", "`a" },
  { "0061_0301", "'a" },
  { "0061_0302", "^a" },
  { "0061_0303", "~a" },
  { "0061_0308", ":a" },
  { "0061_030A", "oa" },
  { "0062", "b" },
  { "0063", "c" },
  { "0063_0301", "'c" },
  { "0063_0327", ",c" },
  { "0064", "d" },
  { "0065", "e" },
  { "0065_0300", "`e" },
  { "0065_0301", "'e" },
  { "0065_0302", "^e" },
  { "0065_0308", ":e" },
  { "0066", "f" },
  { "0066_0066", "ff" },
  { "0066_0066_0069", "Fi" },
  { "0066_0066_006C", "Fl" },
  { "0066_0069", "fi" },
  { "0066_006C", "fl" },
  { "0067", "g" },
  { "0068", "h" },
  { "0069", "i" },
  { "0069_0300", "`i" },
  { "0069_0301", "'i" },
  { "0069_0302", "^i" },
  { "0069_0308", ":i" },
  { "006A", "j" },
  { "006B", "k" },
  { "006C", "l" },
  { "006D", "m" },
  { "006E", "n" },
  { "006E_0303", "~n" },
  { "006F", "o" },
  { "006F_0300", "`o" },
  { "006F_0301", "'o" },
  { "006F_0302", "^o" },
  { "006F_0303", "~o" },
  { "006F_0308", ":o" },
  { "0070", "p" },
  { "0071", "q" },
  { "0072", "r" },
  { "0073", "s" },
  { "0073_030C", "vs" },
  { "0074", "t" },
  { "0075", "u" },
  { "0075_0300", "`u" },
  { "0075_0301", "'u" },
  { "0075_0302", "^u" },
  { "0075_0308", ":u" },
  { "0076", "v" },
  { "0077", "w" },
  { "0078", "x" },
  { "0079", "y" },
  { "0079_0301", "'y" },
  { "0079_0308", ":y" },
  { "007A", "z" },
  { "007A_030C", "vz" },
  { "007B", "lC" },
//{ "007B", "{" },
  { "007C", "ba" },
//{ "007C", "or" },
//{ "007C", "|" },
  { "007D", "rC" },
//{ "007D", "}" },
//{ "007E", "a~" },
  { "007E", "ti" },
//{ "007E", "~" },
  { "00A1", "r!" },
  { "00A2", "ct" },
  { "00A3", "Po" },
  { "00A4", "Cs" },
  { "00A5", "Ye" },
  { "00A6", "bb" },
  { "00A7", "sc" },
  { "00A8", "ad" },
  { "00A9", "co" },
  { "00AA", "Of" },
  { "00AB", "Fo" },
  { "00AC", "no" },
//{ "00AC", "tno" },
  { "00AD", "shc" },
  { "00AE", "rg" },
  { "00AF", "a-" },
  { "00B0", "de" },
  { "00B1", "+-" },
//{ "00B1", "t+-" },
  { "00B2", "S2" },
  { "00B3", "S3" },
  { "00B4", "aa" },
//{ "00B4", "\\'" },
  { "00B5", "mc" },
  { "00B6", "ps" },
  { "00B7", "pc" },
  { "00B8", "ac" },
  { "00B9", "S1" },
  { "00BA", "Om" },
  { "00BB", "Fc" },
  { "00BC", "14" },
  { "00BD", "12" },
  { "00BE", "34" },
  { "00BF", "r?" },
  { "00C6", "AE" },
  { "00D0", "-D" },
  { "00D7", "mu" },
//{ "00D7", "tmu" },
  { "00D8", "/O" },
  { "00DE", "TP" },
  { "00DF", "ss" },
  { "00E6", "ae" },
  { "00F0", "Sd" },
  { "00F7", "di" },
//{ "00F7", "tdi" },
  { "00F8", "/o" },
  { "00FE", "Tp" },
  { "0131", ".i" },
  { "0132", "IJ" },
  { "0133", "ij" },
  { "0141", "/L" },
  { "0142", "/l" },
  { "0152", "OE" },
  { "0153", "oe" },
  { "0192", "Fn" },
  { "02C7", "ah" },
  { "02D8", "ab" },
  { "02D9", "a." },
  { "02DA", "ao" },
  { "02DB", "ho" },
  { "02DD", "a\"" },
  { "0391", "*A" },
  { "0392", "*B" },
  { "0393", "*G" },
  { "0394", "*D" },
  { "0395", "*E" },
  { "0396", "*Z" },
  { "0397", "*Y" },
  { "0398", "*H" },
  { "0399", "*I" },
  { "039A", "*K" },
  { "039B", "*L" },
  { "039C", "*M" },
  { "039D", "*N" },
  { "039E", "*C" },
  { "039F", "*O" },
  { "03A0", "*P" },
  { "03A1", "*R" },
  { "03A3", "*S" },
  { "03A4", "*T" },
  { "03A5", "*U" },
  { "03A6", "*F" },
  { "03A7", "*X" },
  { "03A8", "*Q" },
  { "03A9", "*W" },
  { "03B1", "*a" },
  { "03B2", "*b" },
  { "03B3", "*g" },
  { "03B4", "*d" },
  { "03B5", "*e" },
  { "03B6", "*z" },
  { "03B7", "*y" },
  { "03B8", "*h" },
  { "03B9", "*i" },
  { "03BA", "*k" },
  { "03BB", "*l" },
  { "03BC", "*m" },
  { "03BD", "*n" },
  { "03BE", "*c" },
  { "03BF", "*o" },
  { "03C0", "*p" },
  { "03C1", "*r" },
  { "03C2", "ts" },
  { "03C3", "*s" },
  { "03C4", "*t" },
  { "03C5", "*u" },
  { "03C6", "*f" },
  { "03C7", "*x" },
  { "03C8", "*q" },
  { "03C9", "*w" },
  { "03D1", "+h" },
  { "03D5", "+f" },
  { "03D6", "+p" },
  { "03F5", "+e" },
//{ "2010", "-" },
  { "2010", "hy" },
  { "2013", "en" },
  { "2014", "em" },
//{ "2018", "`" },
  { "2018", "oq" },
//{ "2019", "'" },
  { "2019", "cq" },
  { "201A", "bq" },
  { "201C", "lq" },
  { "201D", "rq" },
  { "201E", "Bq" },
  { "2020", "dg" },
  { "2021", "dd" },
  { "2022", "bu" },
  { "2030", "%0" },
  { "2032", "fm" },
  { "2033", "sd" },
  { "2039", "fo" },
  { "203A", "fc" },
  { "203E", "rn" },
  { "2044", "f/" },
  { "20AC", "Eu" },
//{ "20AC", "eu" },
  { "210F", "-h" },
//{ "210F", "hbar" },
  { "2111", "Im" },
  { "2118", "wp" },
  { "211C", "Re" },
  { "2122", "tm" },
  { "2135", "Ah" },
  { "215B", "18" },
  { "215C", "38" },
  { "215D", "58" },
  { "215E", "78" },
  { "2190", "<-" },
  { "2191", "ua" },
  { "2192", "->" },
  { "2193", "da" },
  { "2194", "<>" },
  { "2195", "va" },
  { "21B5", "CR" },
  { "21D0", "lA" },
  { "21D1", "uA" },
  { "21D2", "rA" },
  { "21D3", "dA" },
  { "21D4", "hA" },
  { "21D5", "vA" },
  { "2200", "fa" },
  { "2202", "pd" },
  { "2203", "te" },
  { "2205", "es" },
  { "2207", "gr" },
  { "2208", "mo" },
  { "2208_0338", "nm" },
  { "220B", "st" },
  { "220F", "product" },
  { "2211", "sum" },
  { "2212", "mi" },
//{ "2212", "\\-" },
  { "2213", "-+" },
  { "2217", "**" },
  { "221A", "sr" },
  { "221D", "pt" },
  { "221E", "if" },
  { "2220", "/_" },
  { "2227", "AN" },
  { "2228", "OR" },
  { "2229", "ca" },
  { "222A", "cu" },
  { "222B", "is" },
//{ "222B", "integral" },
//{ "2234", "3d" },
  { "2234", "tf" },
  { "223C", "ap" },
  { "2243", "|=" },
  { "2245", "=~" },
//{ "2248", "~=" },
  { "2248", "~~" },
  { "2261", "==" },
  { "2261_0338", "ne" },
  { "2264", "<=" },
  { "2265", ">=" },
  { "226A", ">>" },
  { "226B", "<<" },
  { "2282", "sb" },
  { "2282_0338", "nb" },
  { "2283", "sp" },
  { "2283_0338", "nc" },
  { "2286", "ib" },
  { "2287", "ip" },
  { "2295", "c+" },
  { "2297", "c*" },
  { "22A5", "pp" },
  { "22C5", "md" },
  { "2308", "lc" },
  { "2309", "rc" },
  { "230A", "lf" },
  { "230B", "rf" },
  { "239B", "parenlefttp" },
  { "239C", "parenleftex" },
  { "239D", "parenleftbt" },
  { "239E", "parenrighttp" },
  { "239F", "parenrightex" },
  { "23A0", "parenrightbt" },
//{ "23A1", "bracketlefttp" },
  { "23A2", "bracketleftex" },
//{ "23A3", "bracketleftbt" },
//{ "23A4", "bracketrighttp" },
  { "23A5", "bracketrightex" },
//{ "23A6", "bracketrightbt" },
  { "23A7", "lt" },
//{ "23A7", "bracelefttp" },
  { "23A8", "lk" },
//{ "23A8", "braceleftmid" },
  { "23A9", "lb" },
//{ "23A9", "braceleftbt" },
  { "23AA", "bv" },
//{ "23AA", "braceex" },
//{ "23AA", "braceleftex" },
//{ "23AA", "bracerightex" },
  { "23AB", "rt" },
//{ "23AB", "bracerighttp" },
  { "23AC", "rk" },
//{ "23AC", "bracerightmid" },
  { "23AD", "rb" },
//{ "23AD", "bracerightbt" },
  { "23AF", "an" },
  { "2502", "br" },
  { "251D", "rk" },
  { "2525", "lk" },
  { "256D", "lt" },
  { "256E", "rt" },
  { "256F", "rb" },
  { "2570", "lb" },
  { "25A1", "sq" },
  { "25CA", "lz" },
  { "25CB", "ci" },
  { "261C", "lh" },
  { "261E", "rh" },
  { "2660", "SP" },
  { "2663", "CL" },
  { "2665", "HE" },
  { "2666", "DI" },
  { "2713", "OK" },
  { "27E8", "la" },
  { "27E9", "ra" },
};

// global constructor
static struct unicode_to_glyph_init {
  unicode_to_glyph_init();
} _unicode_to_glyph_init;

unicode_to_glyph_init::unicode_to_glyph_init() {
  for (unsigned int i = 0;
       i < sizeof(unicode_to_glyph_list)/sizeof(unicode_to_glyph_list[0]);
       i++) {
    unicode_to_glyph *utg = new unicode_to_glyph[1];
    utg->value = (char *)unicode_to_glyph_list[i].value;
    unicode_to_glyph_table.define(unicode_to_glyph_list[i].key, utg);
  }
}

const char *unicode_to_glyph_name(const char *s)
{
  unicode_to_glyph *result = unicode_to_glyph_table.lookup(s);
  return result ? result->value : 0;
}
