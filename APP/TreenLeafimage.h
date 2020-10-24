#ifndef __TREENLEAFIMAGE_H
#define __TREENLEAFIMAGE_H 


#include "gui.h"


//static const GUI_COLOR _ColorsSmilie[] = {
//     0xFFFFFF,0x000000,0x70FF70
//};

//static const GUI_LOGPALETTE _PalSmilie = {
//  3,	/* number of entries */
//  1, 	/* Has transparency */
//  &_ColorsSmilie[0]
//};

//static const unsigned char _acSmilie[] = {
//  0x00, 0x55, 0x40, 0x00,
//  0x01, 0xAA, 0x90, 0x00,
//  0x06, 0xAA, 0xA4, 0x00,
//  0x19, 0x6A, 0x59, 0x00,
//  0x69, 0x6A, 0x5A, 0x40,
//  0x6A, 0xA6, 0xAA, 0x40,
//  0x6A, 0xA6, 0xAA, 0x40,
//  0x6A, 0xA6, 0xAA, 0x40,
//  0x6A, 0xAA, 0xAA, 0x40,
//  0x1A, 0x6A, 0x69, 0x00,
//  0x06, 0x95, 0xA4, 0x00,
//  0x01, 0xAA, 0x90, 0x00,
//  0x00, 0x55, 0x40, 0x00
//};

//static const GUI_BITMAP _bmSmilie = {
// 13, /* XSize */
// 13, /* YSize */
// 4,  /* BytesPerLine */
// 2,  /* BitsPerPixel */
// (unsigned char *)_acSmilie,   /* Pointer to picture data (indices) */
// &_PalSmilie  /* Pointer to palette */
//};






//extern GUI_CONST_STORAGE GUI_BITMAP bmtxt;

//static GUI_CONST_STORAGE GUI_COLOR _Colorstxt[] = {
//  0xFFFFFF, 0xFFFEFC, 0xFFFFFE, 0xDEC6C6,
//  0xFFFCF8, 0xFFFCFA, 0xFFFFFB, 0xFFFFFC,
//  0x3C4A5A, 0x554141, 0x594444, 0x594544,
//  0x66504F, 0xAB7E6A, 0xBF8F75, 0xBB8C7A,
//  0xBF8F7D, 0x5C7B97, 0x747C87, 0x677E96,
//  0x607F9B, 0x437CA4, 0x437DA5, 0x467FA5,
//  0x4D5CC3, 0x617DEF, 0x4786A6, 0x4881A5,
//  0x4983A6, 0x4885A6, 0x4288A6, 0x418AA6,
//  0x4688A6, 0x438CA5, 0x4480AC, 0x73ADBF,
//  0x38B1FA, 0x3EB1FA, 0x3CB5FF, 0x3FBBFF,
//  0x7AACC2, 0x7CB0C2, 0x7FB3C7, 0x43BAFF,
//  0x42BFFF, 0x52B7F5, 0x51BBF8, 0x52BBFF,
//  0x38C8FD, 0x3ECEFE, 0x3FD3FF, 0x4EC0E3,
//  0x56C4EB, 0x5FC8F1, 0x50CEFC, 0x42D1FE,
//  0x44D8FF, 0x48DCFF, 0x54D3FD, 0x57D7FF,
//  0x6CCDFF, 0x75C9FC, 0x71CFFF, 0x7BCFFA,
//  0x7CCCF9, 0x78CBFC, 0x6FD0FD, 0x6AD5FF,
//  0x75DBFF, 0xAC8E82, 0xAF938C, 0xB39486,
//  0xB4978C, 0xB69A91, 0xB79D94, 0xBA9F97,
//  0x8183BB, 0xB6AFAA, 0xBDB0A5, 0xCD9B86,
//  0xCDA098, 0xCDAAAA, 0xD1BBBB, 0xD8BEBC,
//  0xDABFBF, 0xCEC5BF, 0xF8CBAB, 0xEFC8BC,
//  0x85B1C4, 0x81B6C8, 0x9DBDC7, 0xAAB0D8,
//  0x85CADF, 0xB2C1DC, 0x8BCFFA, 0x80D7FE,
//  0x89D6FB, 0x8ED7FD, 0x8CDEFF, 0x92D2F9,
//  0x91DAFB, 0x97D9FD, 0x93DFFF, 0xB4D8E3,
//  0xB8D9E3, 0xBADAE4, 0x97E8F9, 0xA1ECFC,
//  0xA4ECFD, 0xBDF7FF, 0xDBC2C1, 0xDCC3C3,
//  0xDDC4C4, 0xDDC5C5, 0xDEC6C5, 0xC9CBD9,
//  0xC7DADE, 0xFAD1C5, 0xF3D1CB, 0xF7D7CF,
//  0xE3DED5, 0xE8DDD1, 0xEBDED5, 0xE9D8D8,
//  0xEBDBDB, 0xEDDCDC, 0xEFDEDE, 0xF7D9D1,
//  0xF4DDD8, 0xF6DFDA, 0xF4DFDD, 0xF4E7D8,
//  0xF1E0DF, 0xF3E0DF, 0xF6E9DD, 0xFDECDB,
//  0xFAE8DE, 0xFFECDE, 0xFFF1DF, 0xE2E1E9,
//  0xE9E8E8, 0xEEEDE8, 0xEDEFEB, 0xF0EBE3,
//  0xF0EEE7, 0xFFEFE2, 0xFBEEE6, 0xFAEEE7,
//  0xFDEFE5, 0xFFF5E0, 0xFFF1E6, 0xFAF1EA,
//  0xFEF3E9, 0xFDF3EA, 0xFEF3EB, 0xFFF5EA,
//  0xFCF2ED, 0xFDF4EF, 0xFFF6EE, 0xFFF7EF,
//  0xFFF8E8, 0xFFF8EC, 0xFFFBED, 0xFFFBEF,
//  0xECF3F1, 0xF1F0F3, 0xF8F4F1, 0xF9F4F1,
//  0xFBF6F1, 0xFEF6F0, 0xFDF6F3, 0xFDF7F3,
//  0xF8F8F3, 0xFEF9F3, 0xFFF9F3, 0xFEF8F4,
//  0xFEF9F5, 0xFEFBF4, 0xFFFBF6, 0xFEFAF7,
//  0xF4F9FA, 0xF4FCFD, 0xF5FDFF, 0xFFFDF9,
//  0xFEFCFA, 0xFFFDFA, 0xFFFFFD
//};

//static GUI_CONST_STORAGE GUI_LOGPALETTE _Paltxt = {
//  187,  // Number of entries
//  0,    // No transparency
//  &_Colorstxt[0]
//};

//static GUI_CONST_STORAGE unsigned char _actxt[] = {
//  0x00, 0x51, 0x7B, 0x7C, 0x7D, 0x7E, 0x84, 0x85, 0x82, 0x80, 0x76, 0x50, 0x0D, 0x10, 0x0A,
//  0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xAD, 0x88, 0x57, 0x0E, 0x0F, 0x0B,
//  0x00, 0x03, 0x00, 0x02, 0x8B, 0x5B, 0xA5, 0x06, 0xB3, 0xAF, 0x93, 0x77, 0x56, 0x4F, 0x09,
//  0x00, 0x72, 0x00, 0xB1, 0x18, 0x19, 0x73, 0xAC, 0xB7, 0xB0, 0x9C, 0x81, 0x7F, 0x75, 0x0C,
//  0x00, 0x71, 0x00, 0x06, 0x4C, 0x5D, 0x6D, 0x67, 0xA7, 0x04, 0xAB, 0x9D, 0x92, 0x89, 0x46,
//  0x00, 0x70, 0x00, 0x02, 0xAE, 0x5A, 0x35, 0x6C, 0x68, 0xA6, 0xB2, 0xA9, 0x99, 0xA1, 0x4B,
//  0x00, 0x6F, 0x00, 0x01, 0x02, 0xAA, 0x2A, 0x34, 0x6B, 0x69, 0x97, 0x9E, 0x98, 0xA3, 0x4A,
//  0x00, 0x6E, 0x00, 0x01, 0x05, 0xBA, 0xA8, 0x59, 0x33, 0x6A, 0x74, 0x94, 0x96, 0xA2, 0x49,
//  0x00, 0x54, 0x00, 0x01, 0x05, 0xB8, 0x07, 0x9A, 0x23, 0x5C, 0x8C, 0x7A, 0x91, 0xA0, 0x48,
//  0x00, 0x53, 0x00, 0x07, 0xB9, 0x04, 0x9F, 0x9B, 0x86, 0x55, 0x4D, 0x4E, 0x8A, 0x95, 0x47,
//  0x00, 0x52, 0xB6, 0xB5, 0xB4, 0xA4, 0x8E, 0x8D, 0x90, 0x8F, 0x78, 0x79, 0x83, 0x87, 0x45,
//  0x00, 0x58, 0x3B, 0x3A, 0x36, 0x64, 0x60, 0x3F, 0x40, 0x63, 0x5E, 0x2E, 0x2D, 0x2F, 0x13,
//  0x00, 0x28, 0x37, 0x31, 0x30, 0x5F, 0x42, 0x61, 0x65, 0x41, 0x3D, 0x24, 0x25, 0x26, 0x11,
//  0x00, 0x29, 0x39, 0x38, 0x32, 0x44, 0x43, 0x62, 0x66, 0x3E, 0x3C, 0x27, 0x2B, 0x2C, 0x14,
//  0x00, 0x12, 0x21, 0x1F, 0x1E, 0x20, 0x1A, 0x1D, 0x1C, 0x1B, 0x17, 0x16, 0x15, 0x22, 0x08
//};

//GUI_CONST_STORAGE GUI_BITMAP _bmtxt = {
//  15, // xSize
//  15, // ySize
//  15, // BytesPerLine
//  8, // BitsPerPixel
//  (unsigned char *)_actxt,  // Pointer to picture data (indices)
//  &_Paltxt   // Pointer to palette
//};

//static GUI_CONST_STORAGE GUI_COLOR _Colorsmusic[] = {
//  0xFFFFFF, 0xFFFFFF, 0x9C3E00, 0x7E2F00,
//  0x7E3000, 0x823000, 0x843300, 0x7E2E00,
//  0x7F3200, 0x803300, 0x893500, 0x7C2B00,
//  0x7D3100, 0x7D3200, 0x823100, 0x833400,
//  0x843500, 0x873600, 0x8B3800, 0x8B3900,
//  0x762400, 0x772600, 0x772700, 0x772900,
//  0x792800, 0x7A2C00, 0x7C2C00, 0x7C2E00,
//  0x7C2F00, 0x7D2F00, 0x7C2F06, 0x7C3000,
//  0x7C3100, 0x7E3100, 0x7F3100, 0x7E3002,
//  0x7E3303, 0x7F3303, 0x802D00, 0x803200,
//  0x863100, 0x803400, 0x833500, 0x833501,
//  0x843400, 0x853500, 0x853501, 0x863400,
//  0x863500, 0x863600, 0x883300, 0x883500,
//  0x883600, 0x883700, 0x893601, 0x8B3600,
//  0x843B00, 0x863A01, 0x8A3800, 0x8D3900,
//  0x8A3D01, 0x8F3E04, 0x8E3D09, 0x933900,
//  0x903B03, 0x943B02, 0x9A3C00, 0x9D3E00,
//  0x9D3F00, 0x913F0A, 0x843912, 0x904003,
//  0x914103, 0x984506, 0x91400C, 0x90400D,
//  0x94440F, 0x9F480F, 0x985602, 0x9A5D04,
//  0x9E5F04, 0x8F4313, 0x8F4617, 0x8C431B,
//  0x904112, 0x924613, 0x944716, 0x91471A,
//  0x93471A, 0x90461D, 0x90491A, 0x92481D,
//  0x974D1E, 0xA74605, 0xAB4E0A, 0xB54700,
//  0xB74700, 0xB64900, 0xB74A00, 0xB54903,
//  0xB54A02, 0xB74C05, 0xB54F07, 0xA55907,
//  0xBA510B, 0xB8500D, 0xB8520F, 0xBA5917,
//  0xBB5B1C, 0xBC5D1E, 0xA26604, 0xB6620F,
//  0xAC7007, 0xAE7705, 0xAF7802, 0xAF7807,
//  0xB47302, 0xB07604, 0xB37B03, 0xBF780C,
//  0xBA7915, 0x984E20, 0x9C542B, 0xA45B2C,
//  0xA25B31, 0xBE6226, 0xBE6328, 0xBF652A,
//  0xBD652E, 0xAB643A, 0xBD6932, 0xC37A18,
//  0xD27115, 0xE17618, 0xC76B2E, 0xC96E33,
//  0xDC7632, 0xD67A3F, 0xAA6A42, 0xB97145,
//  0xB27248, 0xC37744, 0xC67746, 0xCF7741,
//  0xB88205, 0xB88506, 0xBA8607, 0xBF8C07,
//  0xC59504, 0xD18110, 0xD0841F, 0xDF9A13,
//  0xD1A506, 0xF1AE19, 0xDA8F30, 0xE48426,
//  0xE68824, 0xEE9729, 0xE58633, 0xF1A022,
//  0xF1A93A, 0xDC8B55, 0xE88D4B, 0xE8934F,
//  0xE29B48, 0xE58D52, 0xED9C53, 0xEDA44E,
//  0xD99F78, 0xE59B67, 0xE79E6E, 0xEAA866,
//  0xEBA16C, 0xEBA678, 0xF3AD72, 0xF3B181,
//  0xF1B58B, 0xF0B78E
//};

//static GUI_CONST_STORAGE GUI_LOGPALETTE _Palmusic = {
//  178,  // Number of entries
//  1,    // Has transparency
//  &_Colorsmusic[0]
//};

//static GUI_CONST_STORAGE unsigned char _acmusic[] = {
//  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x46, 0x59, 0x7C, 0x8A, 0x00,
//  0x00, 0x00, 0x00, 0x00, 0x41, 0x53, 0x7A, 0x81, 0x8B, 0x8E, 0x8F, 0x89, 0x88, 0x68, 0x00,
//  0x00, 0x00, 0x00, 0x00, 0x4A, 0xA1, 0xAA, 0xAD, 0xAC, 0xA3, 0x9E, 0x9B, 0x85, 0x61, 0x00,
//  0x00, 0x00, 0x00, 0x00, 0x4B, 0xA9, 0xAB, 0xA4, 0x9A, 0x96, 0x83, 0x78, 0x6F, 0x63, 0x00,
//  0x00, 0x00, 0x00, 0x00, 0x58, 0x87, 0x74, 0x90, 0x94, 0x91, 0x00, 0x00, 0x45, 0x69, 0x00,
//  0x00, 0x00, 0x00, 0x00, 0x5B, 0x80, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x56, 0x6C, 0x00,
//  0x00, 0x00, 0x00, 0x00, 0x57, 0x7F, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79, 0x7E, 0x00,
//  0x00, 0x00, 0x00, 0x00, 0x51, 0x6D, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5C, 0x7D, 0x00,
//  0x00, 0x00, 0x00, 0x00, 0x3E, 0x6A, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x54, 0x6B, 0x00,
//  0x00, 0x00, 0x00, 0x00, 0x36, 0x64, 0x0D, 0x00, 0x00, 0x00, 0x52, 0x8C, 0x82, 0x65, 0x00,
//  0x00, 0x00, 0x23, 0x5A, 0x4D, 0x5F, 0x0D, 0x00, 0x00, 0x7B, 0xB1, 0xAF, 0xA2, 0x62, 0x00,
//  0x33, 0x55, 0xA8, 0xB0, 0xA5, 0x60, 0x20, 0x00, 0x0E, 0x86, 0xA6, 0xA0, 0x9F, 0x5E, 0x00,
//  0x4C, 0x8D, 0xAE, 0xA7, 0x9D, 0x66, 0x00, 0x00, 0x00, 0x42, 0x84, 0x97, 0x77, 0x3D, 0x00,
//  0x37, 0x5D, 0x9C, 0x99, 0x95, 0x40, 0x00, 0x00, 0x00, 0x00, 0x25, 0x50, 0x00, 0x00, 0x00,
//  0x00, 0x2A, 0x49, 0x67, 0x4E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//};

//GUI_CONST_STORAGE GUI_BITMAP _bmmusic = {
//  15, // xSize
//  15, // ySize
//  15, // BytesPerLine
//  8, // BitsPerPixel
//  (unsigned char *)_acmusic,  // Pointer to picture data (indices)
//  &_Palmusic   // Pointer to palette
//};

//static GUI_CONST_STORAGE GUI_COLOR _Colorsbin[] = {
//  0xFFFFFF, 0xFFFFFF, 0xF6F6F7, 0x070707,
//  0x626262, 0x686868, 0x040404, 0x09090A,
//  0x0C0C0C, 0x0C0C0D, 0x0D0D0D, 0x0F0F10,
//  0x101010, 0x111111, 0x151515, 0x161616,
//  0x171818, 0x1B1B1B, 0x1C1C1C, 0x1E1F1C,
//  0x143014, 0x1F1F20, 0x073D3D, 0x202020,
//  0x242424, 0x242626, 0x272A22, 0x232F20,
//  0x242C21, 0x292929, 0x2D2D2E, 0x2E2E2F,
//  0x2F2F30, 0x342E31, 0x323232, 0x333333,
//  0x343434, 0x363636, 0x3E3C3A, 0x3C3C3C,
//  0x3D3D3D, 0x3F3E3C, 0x4C2239, 0x403230,
//  0x49303E, 0x5D5513, 0x46453B, 0x5B4E3B,
//  0x5C084C, 0x67334F, 0x27635F, 0x454641,
//  0x43494D, 0x49494A, 0x4F4F4F, 0x57484E,
//  0x515151, 0x5F5252, 0x5D5850, 0x59595A,
//  0x664956, 0x467542, 0x4B5C61, 0x7C4F71,
//  0x5B6C6E, 0x636363, 0x6A6A6A, 0x707070,
//  0x717172, 0x8A7532, 0x983C7B, 0x81547A,
//  0x905B74, 0xB47E7B, 0xE05E59, 0xFA7C6F,
//  0x1B9318, 0x2C842A, 0x3FA736, 0x569F53,
//  0x59CB40, 0x74E568, 0xB58B5A, 0x80BD76,
//  0xD6AA64, 0x82C35D, 0x00019F, 0x2D5383,
//  0x316189, 0x4654A7, 0x6969A8, 0x8B5A83,
//  0xBB6EA5, 0xEC5FBA, 0x827DE5, 0xE951C1,
//  0xE37ACF, 0x5DA29F, 0x74B081, 0x4387A6,
//  0x35A2C9, 0x6DB5CC, 0x64B6E6, 0x73CCC0,
//  0x5DC3F6, 0x848484, 0x898989, 0x8F8E8E,
//  0x92918E, 0x979A93, 0x979798, 0x9C9D98,
//  0x9E9E9E, 0xA5A3A2, 0xA5A4A4, 0xA5A6A6,
//  0xADAAA8, 0xAFACAA, 0xAEAEAA, 0xB0AEAD,
//  0xB1AFAE, 0xB1B0AE, 0xB5B5B6, 0xB7B7BA,
//  0xBABBBB, 0xBDBDBD, 0xCC8391, 0xD9819B,
//  0xD29290, 0xFA9A83, 0x99F081, 0xB0EB8E,
//  0xB8E2AF, 0xEED59A, 0xD7D1A4, 0xC4C1BF,
//  0xCCFFBC, 0x8B8EE3, 0x9A96E5, 0x9499EA,
//  0x9AA2E8, 0x9CA0E9, 0x88B1EB, 0xED97DE,
//  0xFA8DE3, 0xF699EB, 0xA9DCF6, 0xA7EAF9,
//  0xB7FBFF, 0xC0C0C0, 0xC0C4C4, 0xC4C4C4,
//  0xC7C6C4, 0xC8C4C2, 0xCAC6C4, 0xC3C8C3,
//  0xC8C8C7, 0xCBC8C6, 0xCAC8C7, 0xCBCBC7,
//  0xC7C7C8, 0xC8C8C8, 0xCBCAC8, 0xCBCBC9,
//  0xC9C9CA, 0xCBCACA, 0xCECDCE, 0xCFCECE,
//  0xCDD1D4, 0xD2D3D1, 0xD5D4D3, 0xD0D5D5,
//  0xD4D4D4, 0xD4D4D5, 0xD4DADC, 0xDDDCDB,
//  0xDDDDDD, 0xDDDDDE, 0xE6C6E3, 0xFECEFB,
//  0xE3E2E3, 0xE6E7E7, 0xE9ECEA, 0xECEDED,
//  0xEDF3EE, 0xF2ECF1, 0xF5F5F6, 0xF5F6F6,
//  0xF4F7F6, 0xF8F8F9
//};

//static GUI_CONST_STORAGE GUI_LOGPALETTE _Palbin = {
//  190,  // Number of entries
//  1,    // Has transparency
//  &_Colorsbin[0]
//};

//static GUI_CONST_STORAGE unsigned char _acbin[] = {
//  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//  0x00, 0xB1, 0xBA, 0x02, 0x02, 0x02, 0x02, 0x02, 0xBB, 0xB7, 0xB8, 0xBC, 0xBD, 0x95, 0x00,
//  0x00, 0xAD, 0xAA, 0x9E, 0x99, 0x9A, 0x9D, 0xA2, 0xA3, 0xB9, 0xB2, 0x9B, 0xA9, 0x7D, 0x00,
//  0x00, 0xA4, 0x3A, 0x2E, 0x40, 0x3E, 0x34, 0x29, 0x37, 0xB3, 0x91, 0x46, 0x39, 0x7C, 0x38,
//  0x00, 0x9C, 0x5A, 0x59, 0x92, 0x93, 0x66, 0x58, 0x2B, 0x47, 0x8F, 0x5D, 0x3C, 0xB6, 0x04,
//  0x00, 0x9F, 0x8B, 0x56, 0x8E, 0x94, 0x68, 0x63, 0x3D, 0x1C, 0x2C, 0x31, 0x33, 0xB4, 0x28,
//  0x00, 0x98, 0x8D, 0x57, 0x61, 0x67, 0x64, 0x65, 0x88, 0x4F, 0x1B, 0x13, 0x26, 0xA6, 0x1D,
//  0x00, 0xA7, 0x8C, 0x84, 0x83, 0x55, 0x4D, 0x32, 0x53, 0x82, 0x4E, 0x14, 0x21, 0x7A, 0x0E,
//  0x97, 0xAF, 0x89, 0x62, 0x51, 0x50, 0x4C, 0x16, 0x3F, 0x5C, 0x48, 0x2A, 0x19, 0x73, 0x00,
//  0xA1, 0xB0, 0x5E, 0x49, 0x52, 0x45, 0x2D, 0x2F, 0x7E, 0x90, 0x5F, 0x30, 0x1A, 0x72, 0x00,
//  0xAC, 0xB5, 0x8A, 0x80, 0x81, 0x4B, 0x4A, 0x85, 0x54, 0x7F, 0x60, 0x5B, 0x86, 0x79, 0x00,
//  0x6A, 0x6E, 0x76, 0x96, 0xA8, 0xAE, 0xAB, 0x87, 0x75, 0x6F, 0x6D, 0x6C, 0x7B, 0x44, 0x00,
//  0x00, 0x00, 0x08, 0x12, 0x23, 0x36, 0x43, 0x6B, 0x71, 0x77, 0x78, 0x74, 0xA5, 0x1F, 0x00,
//  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x10, 0x1E, 0x35, 0x3B, 0x17, 0x00,
//  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//};

//GUI_CONST_STORAGE GUI_BITMAP _bmbin = {
//  15, // xSize
//  15, // ySize
//  15, // BytesPerLine
//  8, // BitsPerPixel
//  (unsigned char *)_acbin,  // Pointer to picture data (indices)
//  &_Palbin   // Pointer to palette
//};

//static GUI_CONST_STORAGE GUI_COLOR _Colorslrc[] = {
//  0xFFFFFF, 0x000000, 0xFFFFFF, 0xC0F6FF,
//  0x000200, 0x030304, 0x050607, 0x040A04,
//  0x0F0C05, 0x0E080A, 0x120504, 0x120705,
//  0x140607, 0x120905, 0x120C05, 0x140609,
//  0x140709, 0x0C1A10, 0x141917, 0x293C32,
//  0x462B38, 0x573534, 0x573B34, 0x5A373A,
//  0x4E4B36, 0x574234, 0x584B34, 0x5B3744,
//  0x5B3840, 0x324E44, 0x2D584C, 0x305E58,
//  0x3B4572, 0x3D5F74, 0x356565, 0x366468,
//  0x3C6571, 0x64705E, 0x44607F, 0x6F996A,
//  0x739263, 0x7C9261, 0x689E70, 0x67AA7B,
//  0x475C84, 0x506190, 0x6A76AE, 0x7377AF,
//  0x6778B3, 0x7E78B1, 0xA97F9E, 0x9F7DA0,
//  0x9E7BA5, 0x9D7BAD, 0x8B79B2, 0x977AB3,
//  0x9D7BB3, 0x6FB78B, 0x7EC9A6, 0x8F9C9F,
//  0xAABBC5, 0x91DBC4, 0xABCEDC, 0xABCFDE,
//  0xAACFDF, 0xB3C8D2, 0xADD0D9, 0xACD0DA,
//  0xADD2DB, 0xAED6DA, 0xACD1DD, 0xADD3DC,
//  0xACD0DF, 0xADD5DC, 0xAFD7DD, 0xAFDADE,
//  0xAFDBDE, 0xABDEDD, 0xAFDCDD, 0xB0DEDF,
//  0xA9CEE0, 0xABCEE0, 0xA4D4E3, 0xA8D0E3,
//  0xAFDFE0, 0xAEDFE1, 0xA9DBE7, 0xAFDBE5,
//  0xAEDDE7, 0xAEDFE7, 0xADD7EB, 0xA8DDE9,
//  0xACDCE8, 0xB0DBE3, 0xB2DFE2, 0xB2DDE4,
//  0xB0D9EA, 0xB1DAEA, 0xB1DBF0, 0xABE1E1,
//  0xADE1E2, 0xAFE1E2, 0xACE2E4, 0xAEE3E5,
//  0xACE2E6, 0xA9E1EB, 0xACE3E9, 0xAEE5E9,
//  0xA9E5ED, 0xB1E1E3, 0xB4E3E7, 0xB2E0EA,
//  0xB3E2EA, 0xB3E6EB, 0xB4E4EA, 0xB4E5EA,
//  0xB5E4EB, 0xB3E2ED, 0xB2E7EE, 0xB7E5ED,
//  0xB5E6ED, 0xB4E7ED, 0xB6E6EC, 0xB6E4EF,
//  0xB5E6EF, 0xB3E8ED, 0xADF7E5, 0xAEE2F0,
//  0xADECF1, 0xB1E7F1, 0xB4E7F5, 0xB3E9F0,
//  0xB3EBF1, 0xB4E9F0, 0xB4E9F2, 0xB6ECF1,
//  0xB6ECF3, 0xB4EAF4, 0xB5EAF4, 0xB6EBF6,
//  0xB6EBF7, 0xB4EDF5, 0xB8EEF5, 0xB8ECF7,
//  0xB6EFFA, 0xB8EAFA, 0xBAF0F9, 0xBBF2FB,
//  0xBAF2FC, 0xBDF4FF, 0xBFF4FF, 0xC1DBE9,
//  0xC0E0E6, 0xC7EFEE, 0xC8EBE8, 0xC9EBEF,
//  0xCAE8F0, 0xCCE9F3
//};

//static GUI_CONST_STORAGE GUI_LOGPALETTE _Pallrc = {
//  158,  // Number of entries
//  1,    // Has transparency
//  &_Colorslrc[0]
//};

//static GUI_CONST_STORAGE unsigned char _aclrc[] = {
//  0x00, 0x00, 0x09, 0x0F, 0x10, 0x0C, 0x0A, 0x0B, 0x0D, 0x0E, 0x08, 0x00, 0x00, 0x00, 0x00,
//  0x00, 0x00, 0x14, 0x1B, 0x1C, 0x17, 0x15, 0x16, 0x19, 0x1A, 0x18, 0x06, 0x00, 0x00, 0x00,
//  0x00, 0x01, 0x32, 0x97, 0x3C, 0x41, 0x9D, 0x9C, 0x9B, 0x99, 0x9A, 0x3B, 0x05, 0x00, 0x00,
//  0x00, 0x01, 0x33, 0x94, 0x52, 0x7F, 0x90, 0x8D, 0x84, 0x88, 0x7B, 0x98, 0x25, 0x00, 0x00,
//  0x00, 0x01, 0x34, 0x03, 0x91, 0x8C, 0x8A, 0x85, 0x79, 0x7A, 0x74, 0x78, 0x29, 0x00, 0x00,
//  0x00, 0x01, 0x35, 0x96, 0x82, 0x89, 0x83, 0x7D, 0x73, 0x6E, 0x5F, 0x77, 0x28, 0x00, 0x00,
//  0x00, 0x01, 0x38, 0x03, 0x8B, 0x86, 0x76, 0x71, 0x72, 0x70, 0x6F, 0x7C, 0x27, 0x00, 0x00,
//  0x00, 0x01, 0x37, 0x95, 0x81, 0x6B, 0x67, 0x6D, 0x5E, 0x5D, 0x57, 0x75, 0x2A, 0x00, 0x00,
//  0x00, 0x01, 0x36, 0x93, 0x6A, 0x66, 0x65, 0x4F, 0x4A, 0x44, 0x48, 0x61, 0x2B, 0x01, 0x00,
//  0x00, 0x01, 0x31, 0x92, 0x68, 0x64, 0x54, 0x4B, 0x47, 0x46, 0x40, 0x60, 0x39, 0x04, 0x00,
//  0x00, 0x01, 0x2F, 0x8E, 0x63, 0x55, 0x4C, 0x49, 0x43, 0x3F, 0x50, 0x5A, 0x3A, 0x07, 0x00,
//  0x00, 0x01, 0x2E, 0x87, 0x4D, 0x4E, 0x45, 0x42, 0x3E, 0x51, 0x53, 0x62, 0x3D, 0x11, 0x00,
//  0x00, 0x01, 0x30, 0x8F, 0x59, 0x58, 0x5C, 0x56, 0x5B, 0x69, 0x6C, 0x80, 0x7E, 0x13, 0x00,
//  0x00, 0x01, 0x20, 0x2D, 0x2C, 0x26, 0x21, 0x24, 0x23, 0x22, 0x1F, 0x1E, 0x1D, 0x12, 0x01,
//  0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//};

//GUI_CONST_STORAGE GUI_BITMAP _bmlrc = {
//  15, // xSize
//  15, // ySize
//  15, // BytesPerLine
//  8, // BitsPerPixel
//  (unsigned char *)_aclrc,  // Pointer to picture data (indices)
//  &_Pallrc   // Pointer to palette
//};

//static GUI_CONST_STORAGE GUI_COLOR _Colorsgame[] = {
//  0xFFFFFF, 0x000000, 0xFFFFFF, 0x030303,
//  0x080808, 0x121212, 0x161616, 0x1B1B1B,
//  0x393939, 0x494949, 0x4A4A4A, 0x666666,
//  0x686868, 0xD2D2D2, 0xD5D5D5, 0xDEDEDE,
//  0xE5E5E5, 0xE9E9E9, 0xEAEAEA, 0xF7F7F7,
//  0xF9F9F9, 0xFDFDFD, 0x040404, 0x050505,
//  0x060606, 0x0A0A0A, 0x171717, 0x191919,
//  0x1D1D1D, 0x212121, 0x2F2F2F, 0x3A3A3A,
//  0x3D3D3D, 0x444444, 0x484248, 0x484848,
//  0x4C4C4C, 0x515151, 0x525252, 0x575757,
//  0x595959, 0x5A5A5A, 0x5C5C5C, 0x5D5D5D,
//  0x666665, 0x6E6E6E, 0x7B767B, 0x22C523,
//  0x36C033, 0x6767A4, 0x6464A9, 0x7979F2,
//  0x47B5F5, 0x868686, 0x888888, 0x8E8E8E,
//  0x8F8F8F, 0x88889B, 0x939393, 0x959595,
//  0x969696, 0x979797, 0x9A9A9A, 0x9E9E9E,
//  0xA1A1A1, 0xA2A2A2, 0xAAA9AA, 0xAAAAAA,
//  0xABABAB, 0xAEAEAE, 0xAFAFAF, 0xB1B1AF,
//  0xB1B1B1, 0xB2B2B2, 0xB4B4B4, 0xB7B7B7,
//  0xB8B8B8, 0xB9B9B9, 0xBFBFBF, 0x8CC59B,
//  0x93D191, 0xA6CDA6, 0xBAD4BA, 0x8A8AC9,
//  0x9F9FD6, 0xA1A1EF, 0xB0B0F3, 0xA2CCE0,
//  0xA0CEE4, 0xC1C1C2, 0xC2C2C2, 0xC3C3C3,
//  0xC6C6C6, 0xCBCBC5, 0xCCCCC5, 0xC6C6C9,
//  0xCBC9CB, 0xCACACA, 0xCBCBCB, 0xCCCCCC,
//  0xD1CFCE, 0xD8D8CE, 0xCDCDD1, 0xD8CCD3,
//  0xC0D3DC, 0xD3D1D0, 0xD6D6D3, 0xD5D2D5,
//  0xD6D6D6, 0xDADADA, 0xDBDBDB, 0xD8DDD8,
//  0xDBDBDC, 0xDCDCDC, 0xDFDFDE, 0xE1DFDD,
//  0xE0E0DE, 0xDFDFE4, 0xE3DAE3, 0xE1E0E1,
//  0xE2E2E2, 0xE2E2E3, 0xE3E3E3, 0xE0E0E4,
//  0xE2E0E5, 0xE4E4E4, 0xE6E6E6, 0xE7E7E7,
//  0xE9E3E0, 0xECECE5, 0xEBEBEA, 0xECECEB,
//  0xEDEDED, 0xECECEF, 0xEFEFEF, 0xF4EFED,
//  0xF2F2EC, 0xF7F7F4, 0xF8F8F8, 0xFDFDFB,
//  0xFEFEFD
//};

//static GUI_CONST_STORAGE GUI_LOGPALETTE _Palgame = {
//  141,  // Number of entries
//  1,    // Has transparency
//  &_Colorsgame[0]
//};

//static GUI_CONST_STORAGE unsigned char _acgame[] = {
//  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//  0x00, 0x00, 0x00, 0x11, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x02, 0x00, 0x00, 0x00,
//  0x00, 0x00, 0x08, 0x13, 0x85, 0x66, 0x5E, 0x47, 0x5D, 0x5F, 0x75, 0x8C, 0x0C, 0x00, 0x00,
//  0x00, 0x07, 0x0F, 0x6D, 0x74, 0x54, 0x32, 0x39, 0x31, 0x53, 0x79, 0x72, 0x77, 0x08, 0x00,
//  0x00, 0x36, 0x49, 0x29, 0x2C, 0x59, 0x56, 0x33, 0x55, 0x7B, 0x6A, 0x60, 0x6F, 0x42, 0x00,
//  0x1C, 0x0E, 0x2D, 0x0C, 0x0B, 0x35, 0x88, 0x65, 0x81, 0x73, 0x67, 0x50, 0x2F, 0x51, 0x22,
//  0x28, 0x8A, 0x3C, 0x27, 0x26, 0x3B, 0x78, 0x6E, 0x80, 0x58, 0x34, 0x4F, 0x30, 0x52, 0x2E,
//  0x3A, 0x15, 0x7F, 0x4D, 0x43, 0x5B, 0x0D, 0x0E, 0x69, 0x68, 0x57, 0x7C, 0x76, 0x6B, 0x3D,
//  0x48, 0x15, 0x11, 0x7A, 0x7E, 0x6C, 0x44, 0x3E, 0x40, 0x64, 0x87, 0x12, 0x70, 0x63, 0x41,
//  0x46, 0x14, 0x10, 0x7D, 0x5A, 0x0B, 0x0A, 0x23, 0x09, 0x2B, 0x4E, 0x84, 0x71, 0x62, 0x3F,
//  0x37, 0x86, 0x12, 0x45, 0x1F, 0x1B, 0x19, 0x16, 0x04, 0x06, 0x20, 0x4B, 0x0F, 0x61, 0x38,
//  0x24, 0x10, 0x4A, 0x1E, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1A, 0x09, 0x4C, 0x0D, 0x2A,
//  0x03, 0x0A, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1D, 0x25, 0x04,
//  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
//  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//};

//GUI_CONST_STORAGE GUI_BITMAP _bmgame = {
//  15, // xSize
//  15, // ySize
//  15, // BytesPerLine
//  8, // BitsPerPixel
//  (unsigned char *)_acgame,  // Pointer to picture data (indices)
//  &_Palgame   // Pointer to palette
//};

//static GUI_CONST_STORAGE GUI_COLOR _Colorspictures[] = {
//  0xFFFFFF, 0xFFFFFF, 0x777276, 0xBEDFBB,
//  0x787377, 0xDC8D47, 0xE4A765, 0xA6A5A4,
//  0xA6A5A5, 0xA7A6A5, 0xD8D7D5, 0xD8D8D7,
//  0xE5E4DD, 0xE4E4DE, 0x153E0E, 0x0F3711,
//  0x1A3F1D, 0x1B4C1C, 0x23521F, 0x1B4323,
//  0x1D4921, 0x2E6126, 0x39702A, 0x4A7533,
//  0x464646, 0x616260, 0x717170, 0x727071,
//  0x727271, 0x757173, 0x757473, 0x777175,
//  0x777275, 0x777376, 0x787376, 0x797578,
//  0xCA6C25, 0xCE722E, 0xCF742F, 0xD7772D,
//  0xD97928, 0xD07531, 0xD17631, 0xD27834,
//  0xD57B36, 0xD97C31, 0xD97D33, 0xD57C38,
//  0xD77D38, 0xD67E39, 0x8B7F46, 0x65915C,
//  0x6B8473, 0x738E7C, 0x748F7F, 0x928449,
//  0x98884B, 0x9C894D, 0xA28E53, 0xBB995A,
//  0xBE9D59, 0xD88440, 0xD98743, 0xDC8944,
//  0xDC8B47, 0xDC8D46, 0xDC8A48, 0xDC8D4C,
//  0xDE914B, 0xD68F58, 0xDE9656, 0xE1924B,
//  0xE0934F, 0xE19754, 0xE09757, 0xE1A255,
//  0xE4A158, 0xE1A458, 0xE3A559, 0xE5A65A,
//  0xE2A35F, 0xE8A75A, 0xE9A85B, 0xEAA95C,
//  0xEBAA5E, 0xE19E64, 0xC9A160, 0xD4A360,
//  0xDAA867, 0xDFA06C, 0xE2A460, 0xE2A461,
//  0xE3A562, 0xE2A664, 0xE3A766, 0xE4A764,
//  0xEDAC61, 0xECAC62, 0xE3A872, 0xE8AD74,
//  0xE3AB78, 0xE3AC78, 0xE4AD7B, 0xE7B17E,
//  0xE7B77E, 0x739084, 0x70908B, 0x6F94A1,
//  0x7698A6, 0x719BB5, 0x7AA0B2, 0x77A3B8,
//  0x828181, 0x838282, 0x8F8E8D, 0x918D90,
//  0x949493, 0x969394, 0x989797, 0x9BAB94,
//  0x94B1A3, 0x9AB2B8, 0xA5A5A4, 0xA5A5A5,
//  0xA7A5A4, 0xA6A6A5, 0xA7A7A6, 0xA8A5A4,
//  0xB0B0AF, 0xA1BEB2, 0xB5B5B4, 0xB8BAB7,
//  0xBABCB9, 0xBABCBA, 0xBEBDBB, 0xBBBEBC,
//  0xBFBFBE, 0xD8B783, 0xE5B182, 0xE7B485,
//  0xE8B986, 0xE7B68A, 0xE8BA92, 0xE9BD97,
//  0xA2C0B5, 0xBADCB7, 0xBFDEBE, 0xBEE0BB,
//  0xBFE0BB, 0xBFE0BC, 0xE9C29D, 0xC0DFBF,
//  0xE9C1A2, 0xE9C3A2, 0xECCCAF, 0xECCFB0,
//  0xE6D3B6, 0xECD2B1, 0xEDD3B8, 0xC0E0BE,
//  0xBBBFC0, 0xBBBFC2, 0xBCBFC1, 0xAECFCC,
//  0xBDC5C0, 0x9CCAE8, 0xA2D4F7, 0xA8D7F1,
//  0xC3C3C2, 0xD6D4D2, 0xD6D6D4, 0xD7D6D5,
//  0xD7D7D5, 0xD9D7D5, 0xD9DAD8, 0xDCDBD9,
//  0xDCDADA, 0xDEDADA, 0xDFDDDB, 0xDFDDDC,
//  0xE1DBD9, 0xE4DED9, 0xE5DDDB, 0xE0DEDE,
//  0xE5DEDD, 0xD3E7CF, 0xDAE8D8, 0xE4E4DD,
//  0xE5E5DE, 0xDFE4E2, 0xE5E4E3, 0xE4E6E6,
//  0xECE7E3, 0xECE9E4, 0xE3E8EA, 0xE5ECEF,
//  0xEDE9E8, 0xE4EEF4
//};

//static GUI_CONST_STORAGE GUI_LOGPALETTE _Palpictures = {
//  198,  // Number of entries
//  1,    // Has transparency
//  &_Colorspictures[0]
//};

//static GUI_CONST_STORAGE unsigned char _acpictures[] = {
//  0x00, 0x82, 0x7A, 0x07, 0x08, 0x07, 0x08, 0x7C, 0x7F, 0x09, 0x7D, 0x09, 0x7E, 0x7B, 0x74,
//  0x00, 0x72, 0xBE, 0xAF, 0xB2, 0xB7, 0xB3, 0xB0, 0xB1, 0xB4, 0xB5, 0xB6, 0xB8, 0xC4, 0x88,
//  0x00, 0x71, 0xA4, 0x34, 0x35, 0x36, 0x69, 0x6A, 0x6B, 0x6D, 0x6F, 0x6E, 0x6C, 0x79, 0xA8,
//  0x0A, 0xC0, 0xC1, 0x0D, 0x0D, 0xBB, 0x0C, 0x0C, 0xBC, 0xBF, 0xC2, 0xC3, 0xC5, 0xA5, 0xA2,
//  0xAE, 0x45, 0x24, 0x25, 0x26, 0x29, 0x2A, 0x2B, 0x2F, 0x2C, 0x30, 0x27, 0x98, 0xA6, 0xA1,
//  0x0B, 0x59, 0x31, 0x3D, 0x3E, 0x43, 0x42, 0x40, 0x3F, 0x2E, 0x2D, 0x28, 0x99, 0xA7, 0xA0,
//  0x0B, 0x62, 0x05, 0x41, 0x05, 0x46, 0x55, 0x44, 0x4A, 0x48, 0x49, 0x47, 0x9A, 0xA3, 0x87,
//  0x0A, 0x96, 0x66, 0x64, 0x65, 0x8A, 0x8F, 0x8E, 0x8D, 0x8B, 0x67, 0x63, 0x9E, 0x81, 0x85,
//  0xAC, 0x8C, 0x5A, 0x5D, 0x5B, 0x50, 0x5C, 0x5E, 0x06, 0x5F, 0x06, 0x4C, 0x9B, 0x90, 0x84,
//  0xAB, 0x68, 0x4B, 0x4D, 0x4E, 0x4F, 0x52, 0x53, 0x54, 0x60, 0x61, 0x51, 0x9D, 0x78, 0x83,
//  0xAA, 0x89, 0x57, 0x58, 0x56, 0x3B, 0x3A, 0x39, 0x38, 0x32, 0x37, 0x3C, 0x9C, 0xBD, 0x86,
//  0xAD, 0x33, 0x16, 0x17, 0x15, 0x12, 0x11, 0x14, 0x13, 0x0F, 0x10, 0x0E, 0x77, 0x73, 0x18,
//  0xA9, 0xB9, 0x97, 0x92, 0x9F, 0x95, 0x94, 0x93, 0x03, 0x03, 0x03, 0x91, 0xBA, 0x75, 0x00,
//  0x1E, 0x1D, 0x1F, 0x20, 0x02, 0x02, 0x02, 0x21, 0x22, 0x04, 0x04, 0x23, 0x1B, 0x19, 0x00,
//  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//};

//GUI_CONST_STORAGE GUI_BITMAP _bmpictures = {
//  15, // xSize
//  15, // ySize
//  15, // BytesPerLine
//  8, // BitsPerPixel
//  (unsigned char *)_acpictures,  // Pointer to picture data (indices)
//  &_Palpictures   // Pointer to palette
//};

//static GUI_CONST_STORAGE GUI_COLOR _Colorsgif[] = {
//  0xFFFFFF, 0xFFFFFF, 0x000000, 0xB6B8BA,
//  0xECE6DC, 0x010101, 0x030303, 0x060606,
//  0x080808, 0x0C0C0C, 0x101010, 0x131313,
//  0x141212, 0x212121, 0x252525, 0x2D2D2D,
//  0x2E2E2E, 0x3F4040, 0x444545, 0x4E4E4E,
//  0x545455, 0x575657, 0x5D5D5E, 0x6A6A6B,
//  0x717171, 0x26985F, 0x2FA267, 0x37A96E,
//  0x3DB276, 0x256EBF, 0x1C63C9, 0x2977DC,
//  0x4CBE83, 0x56B78F, 0x51B98D, 0x4299B8,
//  0x65B9A6, 0x4CC185, 0x55C48C, 0x53C98C,
//  0x59C093, 0x5ACF93, 0x5DCC94, 0x5DCD95,
//  0x62CA97, 0x60C59D, 0x72CB92, 0x6AD59C,
//  0x71D9A5, 0x77DEAA, 0x71C5BB, 0x7ECDBC,
//  0x71E0A8, 0x2986D8, 0x2F99D8, 0x3FBADC,
//  0x689AD8, 0x7BBEDF, 0x4992E4, 0x808081,
//  0x818181, 0x948E8D, 0x939291, 0x9D9E9F,
//  0xA09998, 0xA49D9A, 0x9FA09F, 0xA3A3A3,
//  0xA3A3A4, 0xA7A5A4, 0xA6A5A5, 0xA6A6A6,
//  0xA8A7A6, 0xA7A7A9, 0xA8A8A9, 0xADA9A8,
//  0xACABA8, 0xB7ADA9, 0xB2AEAC, 0xB1AEAF,
//  0xB3B0AF, 0xB2B1B1, 0xB4B2B2, 0xB4B4B4,
//  0xB7B8BB, 0xB9B9BA, 0xBDBABB, 0xBFBBBB,
//  0xB8B9BC, 0xDC8584, 0xD59690, 0xDF9191,
//  0xD99993, 0xE08E8E, 0xEF9495, 0xD5A39B,
//  0xD0A59C, 0xDAA09C, 0xD9AAA4, 0xC1BAB8,
//  0xC2BCB9, 0xEFA3A3, 0xF0AFB2, 0xE0B8B6,
//  0xEBBDBD, 0x82CAB7, 0x81CEB6, 0x80D3B7,
//  0x83D2BB, 0x93D1B9, 0xC7C2BD, 0xEDC0BB,
//  0xFDDBBF, 0xDEE1B2, 0x85BFCF, 0x83D3CC,
//  0x93D4CC, 0x99DFC8, 0x83DED8, 0x9ADEDD,
//  0xAAC0C3, 0xBCD4CF, 0x86E1DB, 0xABECE4,
//  0xA2ECE8, 0xABE9E8, 0xB0EFED, 0xA5F5F1,
//  0xB6F4F3, 0xB5FFFF, 0xBEFAFA, 0xC0C2C3,
//  0xCDC4C2, 0xCAC9CA, 0xCCC8CA, 0xCFCECE,
//  0xD1CDCC, 0xC4D8D3, 0xD7D1D3, 0xD7D7D8,
//  0xD9D5D8, 0xDCD9DC, 0xFFE0C1, 0xFFEAC3,
//  0xFDE2C8, 0xFDE3C9, 0xFEE4C9, 0xEBE6DB,
//  0xEBE5DC, 0xEFE6DE, 0xF1E8DC, 0xE4F5DF,
//  0xD0DEE2, 0xCCE3E5, 0xC5EDE5, 0xC3F4F4,
//  0xCFF8F2, 0xC5FFFF, 0xCBFDFD, 0xD0FFFB,
//  0xE5E4E5, 0xECEAE3, 0xEEEBE3, 0xEAEBEC,
//  0xF1EFF0
//};

//static GUI_CONST_STORAGE GUI_LOGPALETTE _Palgif = {
//  165,  // Number of entries
//  1,    // Has transparency
//  &_Colorsgif[0]
//};

//static GUI_CONST_STORAGE unsigned char _acgif[] = {
//  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//  0x00, 0x3B, 0x57, 0x63, 0x64, 0x55, 0x54, 0x03, 0x03, 0x03, 0x03, 0x03, 0x58, 0x3C, 0x00,
//  0x00, 0x48, 0xA1, 0x99, 0x98, 0x96, 0x95, 0x94, 0x04, 0x93, 0x04, 0x04, 0xA2, 0x47, 0x00,
//  0x00, 0x4E, 0x39, 0x37, 0x36, 0x78, 0x71, 0x8F, 0x8E, 0x92, 0x90, 0x70, 0x91, 0x53, 0x07,
//  0x00, 0x49, 0x3A, 0x35, 0x1F, 0x23, 0x2E, 0x97, 0x6F, 0x66, 0x5D, 0x59, 0x5B, 0xA4, 0x11,
//  0x00, 0x4C, 0x38, 0x1E, 0x1D, 0x2D, 0x20, 0x75, 0x68, 0x65, 0x5C, 0x5A, 0x61, 0xA0, 0x0D,
//  0x00, 0x46, 0x9A, 0x72, 0x24, 0x2F, 0x26, 0x22, 0x67, 0x5E, 0x5F, 0x60, 0x62, 0x87, 0x08,
//  0x05, 0x4A, 0x9C, 0x9F, 0x2C, 0x30, 0x2A, 0x1A, 0x6D, 0x88, 0x6E, 0x79, 0x89, 0x51, 0x02,
//  0x0C, 0x83, 0x7E, 0x6B, 0x25, 0x31, 0x2B, 0x1B, 0x21, 0x9D, 0x81, 0x7F, 0x7B, 0x42, 0x00,
//  0x0F, 0x8B, 0x9B, 0x28, 0x27, 0x34, 0x29, 0x1C, 0x19, 0x32, 0x7A, 0x76, 0x7C, 0x3F, 0x00,
//  0x15, 0xA3, 0x77, 0x73, 0x33, 0x6C, 0x6A, 0x69, 0x74, 0x7D, 0x80, 0x82, 0x9E, 0x43, 0x00,
//  0x16, 0x44, 0x52, 0x86, 0x8C, 0x8D, 0x8A, 0x84, 0x4D, 0x41, 0x40, 0x3D, 0x56, 0x17, 0x00,
//  0x00, 0x00, 0x02, 0x0B, 0x10, 0x13, 0x18, 0x3E, 0x45, 0x50, 0x4F, 0x4B, 0x85, 0x0A, 0x00,
//  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x09, 0x0E, 0x12, 0x14, 0x06, 0x00,
//  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//};

//GUI_CONST_STORAGE GUI_BITMAP _bmgif = {
//  15, // xSize
//  15, // ySize
//  15, // BytesPerLine
//  8, // BitsPerPixel
//  (unsigned char *)_acgif,  // Pointer to picture data (indices)
//  &_Palgif   // Pointer to palette
//};

//static GUI_CONST_STORAGE GUI_COLOR _Colorsmovie[] = {
//  0xFFFFFF, 0xFFFFFF, 0x1C1B1B, 0x202020,
//  0x232323, 0x727272, 0x898989, 0x959595,
//  0x161615, 0x171616, 0x181411, 0x1B1713,
//  0x1F1A16, 0x191818, 0x1A1A1A, 0x1F1A19,
//  0x1A1D1C, 0x191E1C, 0x1C1C1C, 0x1D1D1D,
//  0x211B18, 0x201D19, 0x281E1D, 0x24211D,
//  0x25221E, 0x242121, 0x252223, 0x242424,
//  0x262626, 0x2E2824, 0x2E2A27, 0x252A2C,
//  0x2D2A2B, 0x2D2F2F, 0x362D27, 0x292D31,
//  0x2E3338, 0x2F363C, 0x303030, 0x313030,
//  0x323232, 0x313435, 0x343434, 0x353535,
//  0x373737, 0x383531, 0x393632, 0x393939,
//  0x393A3A, 0x3B3B3B, 0x3E3D3D, 0x3F3E3C,
//  0x3E3E3D, 0x3E3E3E, 0x45382D, 0x433F3B,
//  0x1E463E, 0x16493F, 0x4C4136, 0x4C4237,
//  0x43403B, 0x144D41, 0x1D5854, 0x1C6254,
//  0x3F5977, 0x326A61, 0x404040, 0x484949,
//  0x4E4D4B, 0x4C4C4D, 0x4E4E4E, 0x524E4B,
//  0x514F4D, 0x515151, 0x525253, 0x575757,
//  0x595551, 0x5B5753, 0x5B5B5B, 0x5D5D5D,
//  0x63574C, 0x615C59, 0x7C7B5E, 0x485665,
//  0x415F7D, 0x41607F, 0x47617F, 0x5F6876,
//  0x636363, 0x696969, 0x6A6A6A, 0x6C6C6B,
//  0x696B6C, 0x6B6D6E, 0x6E6E6E, 0x656675,
//  0x616D7E, 0x7F7871, 0x767878, 0x7C7C7C,
//  0x7F7F7F, 0x8B774F, 0x8B6F53, 0x87705A,
//  0x0E967C, 0x52847D, 0x59A27C, 0x86877B,
//  0xB9956F, 0xA08D77, 0xAA9379, 0xA99D7F,
//  0xCC975C, 0xCF9B5F, 0xD2945F, 0xDBA269,
//  0xC3A579, 0xC5A37E, 0xD8A776, 0xE9A666,
//  0xFDB277, 0x446081, 0x456488, 0x42658C,
//  0x4A6A8B, 0x4F6E8B, 0x4B6D92, 0x4A719B,
//  0x4C749D, 0x547699, 0x62798F, 0x369E8C,
//  0x07A787, 0x57979B, 0x7E8389, 0x6A9A84,
//  0x6584A2, 0x40B5A4, 0x4BBDAF, 0x09D6BB,
//  0x55C1A5, 0x6493C0, 0x68A0D8, 0x6FE1CD,
//  0x848484, 0x878889, 0x8F8F8F, 0x919191,
//  0x9A9A9A, 0xA99A80, 0xBAA281, 0xA1A1A1,
//  0xD4AC85, 0xC7B289, 0xD1B48A, 0xCEB694,
//  0xD9B994, 0xDFBF9D, 0xF4B983, 0xE2BC98,
//  0xDCC198, 0xEDC79E, 0xFAD1A7, 0x87E9D4,
//  0xA9E2C9
//};

//static GUI_CONST_STORAGE GUI_LOGPALETTE _Palmovie = {
//  165,  // Number of entries
//  1,    // Has transparency
//  &_Colorsmovie[0]
//};

//static GUI_CONST_STORAGE unsigned char _acmovie[] = {
//  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//  0x00, 0x4F, 0x97, 0x94, 0x07, 0x07, 0x93, 0x92, 0x06, 0x90, 0x63, 0x05, 0x5A, 0x4E, 0x00,
//  0x00, 0x28, 0x06, 0x46, 0x64, 0x49, 0x05, 0x4B, 0x59, 0x45, 0x4A, 0x43, 0x30, 0x42, 0x00,
//  0x00, 0x34, 0x91, 0x5C, 0x62, 0x5D, 0x5E, 0x5B, 0x58, 0x51, 0x48, 0x44, 0x33, 0x32, 0x00,
//  0x00, 0x4D, 0x9C, 0x95, 0x6B, 0x6F, 0x96, 0x6D, 0x74, 0x9A, 0x73, 0x71, 0x70, 0x3B, 0x00,
//  0x00, 0x4C, 0xA2, 0xA1, 0x9D, 0xA0, 0x9B, 0x6E, 0x9E, 0x8F, 0xA4, 0x78, 0x77, 0x3A, 0x00,
//  0x00, 0x47, 0x9F, 0x98, 0x75, 0x76, 0x6C, 0x66, 0x72, 0x8C, 0x8B, 0xA3, 0x99, 0x36, 0x00,
//  0x00, 0x25, 0x8E, 0x8D, 0x88, 0x86, 0x61, 0x50, 0x67, 0x87, 0x65, 0x6A, 0x52, 0x22, 0x00,
//  0x00, 0x23, 0x80, 0x7B, 0x7E, 0x7F, 0x81, 0x53, 0x82, 0x85, 0x60, 0x5F, 0x57, 0x29, 0x00,
//  0x00, 0x08, 0x3C, 0x18, 0x2D, 0x17, 0x1E, 0x0F, 0x16, 0x41, 0x11, 0x02, 0x09, 0x13, 0x00,
//  0x00, 0x1C, 0x35, 0x31, 0x2A, 0x2B, 0x20, 0x69, 0x89, 0x3F, 0x1A, 0x04, 0x04, 0x12, 0x00,
//  0x00, 0x1B, 0x2F, 0x2C, 0x26, 0x27, 0x21, 0x83, 0x68, 0x38, 0x19, 0x03, 0x03, 0x0E, 0x00,
//  0x00, 0x0D, 0x37, 0x15, 0x2E, 0x0C, 0x1D, 0x3D, 0x39, 0x10, 0x14, 0x0B, 0x0A, 0x02, 0x00,
//  0x00, 0x1F, 0x7D, 0x40, 0x56, 0x7A, 0x7C, 0x8A, 0x00, 0x3E, 0x79, 0x55, 0x54, 0x24, 0x00
//};

//GUI_CONST_STORAGE GUI_BITMAP _bmmovie = {
//  15, // xSize
//  15, // ySize
//  15, // BytesPerLine
//  8, // BitsPerPixel
//  (unsigned char *)_acmovie,  // Pointer to picture data (indices)
//  &_Palmovie   // Pointer to palette
//};

//static GUI_CONST_STORAGE GUI_COLOR _Colorsother[] = {
//  0xFFFFFF, 0x000000, 0xC5963A, 0xDAA549,
//  0x644812, 0x79551F, 0x695020, 0x765A20,
//  0x6D5030, 0x856B2B, 0xC5973B, 0xD29E3B,
//  0xDAA345, 0xEDBB66, 0x37280A, 0x3B2A0A,
//  0x75521F, 0x79531F, 0x79561F, 0x79601F,
//  0x695222, 0x695223, 0x6A572E, 0x69582E,
//  0x69592E, 0x775A20, 0x70502C, 0x745E2D,
//  0x6C5030, 0x6E5D31, 0x715031, 0x7A6020,
//  0x776D2F, 0x786D2F, 0x776C31, 0x776D34,
//  0x786C35, 0x7C6738, 0x7D6839, 0x7E6A3B,
//  0x9D4401, 0xAB5D21, 0x826A2B, 0x876D2B,
//  0x816A36, 0xB57433, 0xFF267C, 0xDE505D,
//  0xC87F46, 0x72FF0F, 0x67FF74, 0xE8812E,
//  0xFF8F3D, 0xB8FF18, 0x81FF31, 0x95FF3F,
//  0xC8FF1A, 0xCAFA25, 0xC38651, 0xC28258,
//  0xD6945E, 0xF49F40, 0xCE9563, 0xD09564,
//  0xD79D71, 0xDDA776, 0xFDA361, 0xEFB666,
//  0xEFB66B, 0xEFB76B, 0xEFB66D, 0xEDB86B,
//  0xEEB86B, 0xF6B265, 0xEBA370, 0xEBB472,
//  0xEEB671, 0xEAB675, 0xEBB676, 0xF0B670,
//  0xFFBA73, 0xFFB877, 0x90FF51, 0xA4FF4B,
//  0xBCFF5E, 0x9EFF62, 0xA1FF61, 0xA6FF71,
//  0xABFF73, 0xD4FF47, 0xD5FB51, 0xFDC479,
//  0xFBC07F, 0xC8FF69, 0xDEFB6D, 0xE5FF62,
//  0xE3FF64, 0xE6FC68, 0x1518FF, 0x3738FF,
//  0x3D64F8, 0x4650FF, 0x5962FD, 0x4779F5,
//  0x4C7DF6, 0x6663FF, 0x646AFF, 0x777AF8,
//  0x797CFF, 0xFF34A2, 0xF96C93, 0xFF6B95,
//  0xFF649A, 0xFF69B7, 0xFF66BB, 0xC435D2,
//  0xFF26C0, 0x8878F9, 0x9D7FF8, 0xFF63CB,
//  0xF665D6, 0xFF64D0, 0x2DFFA0, 0x5DFFAD,
//  0x51FFB3, 0x74FFA8, 0x1AAFFF, 0x1AB5FF,
//  0x27B1FE, 0x6B92F5, 0x7097F6, 0x7D92FA,
//  0x49BEFF, 0x1BD6FF, 0x39F9FF, 0x41FBCF,
//  0x5FFFDC, 0x6BFDDD, 0x55C0FE, 0x40DEFF,
//  0x54D7FF, 0x55DEFF, 0x73CBF9, 0x70C8FE,
//  0x6ED3FF, 0x74D0F9, 0x7AD0F8, 0x4FE3FF,
//  0x4BECFF, 0x59FAFF, 0x5BFCFF, 0x69E6FF,
//  0x74E1F9, 0x70E6FF, 0x75E9FF, 0x71F6FF,
//  0xEBA48F, 0xE2B696, 0xBEFF84, 0xAFFFA0,
//  0xFCCE8B, 0xF9C996, 0xF9CD94, 0xF7CE9E,
//  0xC0FF90, 0xE3FC8D, 0xDEFEA7, 0x8694FF,
//  0x86ABF7, 0x8DA8F1, 0x90A9F2, 0x93AEF2,
//  0x9AB7FA, 0xAEA6FB, 0xB2BCFF, 0xFF8ECE,
//  0xCA95F3, 0x90D6FD, 0x90FEE6, 0x82E8FF,
//  0x92E7FF, 0x9CF2FE, 0xB1E8FF, 0xA0F2FF,
//  0xF5C3D6, 0xC5FAE1
//};

//static GUI_CONST_STORAGE GUI_LOGPALETTE _Palother = {
//  186,  // Number of entries
//  1,    // Has transparency
//  &_Colorsother[0]
//};

//static GUI_CONST_STORAGE unsigned char _acother[] = {
//  0x04, 0x0B, 0x0A, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x0A, 0x0B, 0x04,
//  0x06, 0x0D, 0x0C, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x0C, 0x0D, 0x06,
//  0x14, 0xA2, 0x4B, 0x4E, 0x4D, 0x4C, 0x4F, 0x46, 0x44, 0x45, 0x47, 0x48, 0x43, 0xA0, 0x15,
//  0x1A, 0xA4, 0x52, 0x56, 0x57, 0x7B, 0x7C, 0x88, 0x96, 0x95, 0x9A, 0x97, 0x93, 0xB5, 0x10,
//  0x1E, 0x54, 0x31, 0x36, 0x37, 0x32, 0x7A, 0x87, 0x86, 0x94, 0x8D, 0x8B, 0x85, 0x98, 0x11,
//  0x08, 0x5F, 0x35, 0x53, 0x55, 0x58, 0x7D, 0x89, 0x9B, 0xB3, 0x99, 0x8C, 0x7F, 0x8E, 0x12,
//  0x08, 0x60, 0x38, 0x59, 0x5D, 0x9E, 0x9F, 0xB2, 0xB7, 0xB4, 0x90, 0x84, 0x7E, 0x91, 0x05,
//  0x1C, 0x61, 0x39, 0x5A, 0x5E, 0xA5, 0xA6, 0xB9, 0xB6, 0xB1, 0x8F, 0x8A, 0x80, 0x92, 0x05,
//  0x16, 0x5B, 0x3D, 0x49, 0x5C, 0xA1, 0xA3, 0xB8, 0xAE, 0xAC, 0xA8, 0x82, 0x68, 0xAB, 0x07,
//  0x17, 0x51, 0x34, 0x42, 0x4A, 0x41, 0x9C, 0xAF, 0xB0, 0xA7, 0x83, 0x81, 0x67, 0xAA, 0x07,
//  0x18, 0x50, 0x33, 0x30, 0x3A, 0x3F, 0x6E, 0x72, 0x78, 0x75, 0x6A, 0x66, 0x64, 0xA9, 0x19,
//  0x1D, 0x3C, 0x28, 0x29, 0x2D, 0x2F, 0x2E, 0x6D, 0x74, 0x73, 0x65, 0x63, 0x62, 0x6B, 0x13,
//  0x1B, 0x9D, 0x3B, 0x3E, 0x40, 0x6F, 0x70, 0x71, 0x79, 0x77, 0x76, 0x6C, 0x69, 0xAD, 0x1F,
//  0x0F, 0x2C, 0x27, 0x26, 0x25, 0x24, 0x23, 0x22, 0x20, 0x21, 0x2A, 0x09, 0x2B, 0x09, 0x0E,
//  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
//};

//GUI_CONST_STORAGE GUI_BITMAP _bmother = {
//  15, // xSize
//  15, // ySize
//  15, // BytesPerLine
//  8, // BitsPerPixel
//  (unsigned char *)_acother,  // Pointer to picture data (indices)
//  &_Palother   // Pointer to palette
//};






#endif


