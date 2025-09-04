#include <dirent.h>
#include <sys/stat.h>

#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

#include "gbiex.h"
#include "types.h"

#include "system.h"
#include "fs.h"
#include "data.h"

// for models and font folders
struct ExtTexEntry {
	u16 id;
	u8 name[32];
};

struct ExtTexEntry modelsWithEmbeddedTex[98] = {
	{FILE_CA51GUARD, "Ca51guardZ" }, 					 {FILE_CDD_SHOCK, "Cdd_shockZ" },
	{FILE_CELVIS, "CelvisZ" }, 						     {FILE_CTESTCHR, "CtestchrZ" },
	{FILE_PA51GRATE, "Pa51grateZ" }, 					 {FILE_PAF1ESCAPEDOOR, "Paf1escapedoorZ" },
	{FILE_PAF1_CARGODOOR, "Paf1_cargodoorZ" }, 			 {FILE_PAF1_DOORBIG2, "Paf1_doorbig2Z" },
	{FILE_PAF1_LAMP, "Paf1_lampZ" }, 					 {FILE_PAF1_PHONE, "Paf1_phoneZ" },
	{FILE_PAF1_TOILET, "Paf1_toiletZ" }, 				 {FILE_PAIRBASE_CHAIR2, "Pairbase_chair2Z" },
	{FILE_PAIRBASE_TABLE2, "Pairbase_table2Z" }, 		 {FILE_PAIVILLADOOR1, "Paivilladoor1Z" },
	{FILE_PAIVILLADOOR2A, "Paivilladoor2aZ" }, 			 {FILE_PAIVILLADOOR4, "Paivilladoor4Z" },
	{FILE_PALASKADOOR_IN, "Palaskadoor_inZ" }, 			 {FILE_PALASKADOOR_OUT, "Palaskadoor_outZ" },
	{FILE_PALDOOR_L, "Paldoor_lZ" }, 					 {FILE_PALDOOR_R, "Paldoor_rZ" },
	{FILE_PAL_AIRLOCK, "Pal_airlockZ" }, 				 {FILE_PBODYARMOUR, "PbodyarmourZ" },
	{FILE_PCARDLOCK, "PcardlockZ" }, 					 {FILE_PCASE, "PcaseZ" },
	{FILE_PCETANBLUEGREENL, "PcetanbluegreenlZ" }, 		 {FILE_PCETANBLUEGREENR, "PcetanbluegreenrZ" },
	{FILE_PCETANDOORSIDE, "PcetandoorsideZ" }, 			 {FILE_PCETANDOOR, "PcetandoorZ" },
	{FILE_PCETANSMALLDOOR, "PcetansmalldoorZ" }, 		 {FILE_PCETANWINDOW1, "Pcetanwindow1Z" },
	{FILE_PCETANWINDOW2, "Pcetanwindow2Z" }, 			 {FILE_PCETANWINDOW3, "Pcetanwindow3Z" },
	{FILE_PCHRBRIEFCASE, "PchrbriefcaseZ" }, 			 {FILE_PCHREYESPY, "PchreyespyZ" },
	{FILE_PCIDOOR1_REF, "Pcidoor1_refZ" }, 				 {FILE_PCI_CABINET, "Pci_cabinetZ" },
	{FILE_PCI_CARR_DESK, "Pci_carr_deskZ" }, 			 {FILE_PCI_DESK, "Pci_deskZ" },
	{FILE_PCI_F_CHAIR, "Pci_f_chairZ" }, 				 {FILE_PCI_F_SOFA, "Pci_f_sofaZ" },
	{FILE_PCI_LOUNGER, "Pci_loungerZ" }, 				 {FILE_PCI_TABLE, "Pci_tableZ" },
	{FILE_PCV_CHAIR2, "Pcv_chair2Z" }, 					 {FILE_PCV_LAMP, "Pcv_lampZ" },
	{FILE_PCV_TABLE, "Pcv_tableZ" }, 					 {FILE_PDD_EAR_CHAIR, "Pdd_ear_chairZ" },
	{FILE_PDD_EAR_TABLE, "Pdd_ear_tableZ" }, 			 {FILE_PGOLDENEYELOGO, "PgoldeneyelogoZ" },
	{FILE_PGROUNDGUN, "PgroundgunZ" }, 					 {FILE_PINSTFRONTDOOR, "PinstfrontdoorZ" },
	{FILE_PKEYPADLOCK, "PkeypadlockZ" }, 				 {FILE_PKNOCKKNOCK, "PknockknockZ" },
	{FILE_PMARKER, "PmarkerZ" }, 						 {FILE_PMISC_CRATE, "Pmisc_crateZ" },
	{FILE_PMISC_IRSPECS, "Pmisc_irspecsZ" }, 			 {FILE_PNEWVILLADOOR, "PnewvilladoorZ" },
	{FILE_PNINTENDOLOGO, "PnintendologoZ" }, 			 {FILE_PNLOGO2, "Pnlogo2Z" },
	{FILE_PNLOGO3, "Pnlogo3Z" }, 						 {FILE_PNLOGO, "PnlogoZ" },
	{FILE_PPDFOUR, "PpdfourZ" }, 						 {FILE_PPDMENU, "PpdmenuZ" },
	{FILE_PPDONE, "PpdoneZ" }, 						     {FILE_PPDTHREE, "PpdthreeZ" },
	{FILE_PPDTWO, "PpdtwoZ" }, 						     {FILE_PPEL_CHAIR1, "Ppel_chair1Z" },
	{FILE_PPERFECTDARK, "PperfectdarkZ" }, 				 {FILE_PPOWERNODE, "PpowernodeZ" },
	{FILE_PRARELOGO, "PrarelogoZ" }, 					 {FILE_PRETINALOCK, "PretinalockZ" },
	{FILE_PROOFGUN, "ProofgunZ" }, 						 {FILE_PSECRETINDOOR, "PsecretindoorZ" },
	{FILE_PSHUTTLEDOOR, "PshuttledoorZ" }, 				 {FILE_PSKEDARBRIDGE, "PskedarbridgeZ" },
	{FILE_PSKEDARCONSOLEPANEL, "PskedarconsolepanelZ" }, {FILE_PSKEDARCONSOLE, "PskedarconsoleZ" },
	{FILE_PSKPUZZLEOBJECT, "PskpuzzleobjectZ" }, 		 {FILE_PSK_CONSOLE2, "Psk_console2Z" },
	{FILE_PSK_CRYOPOD1_BOT, "Psk_cryopod1_botZ" }, 		 {FILE_PSK_CRYOPOD1_TOP, "Psk_cryopod1_topZ" },
	{FILE_PSK_FIGHTER1, "Psk_fighter1Z" }, 				 {FILE_PSK_HANGARDOORB_BOT, "Psk_hangardoorb_botZ" },
	{FILE_PSK_HANGARDOORB_TOP, "Psk_hangardoorb_topZ" }, {FILE_PSK_HANGARDOOR_BOT, "Psk_hangardoor_botZ" },
	{FILE_PSK_HANGARDOOR_TOP, "Psk_hangardoor_topZ" }, 	 {FILE_PSK_SHIP_DOOR2, "Psk_ship_door2Z" },
	{FILE_PSK_UNDER_GENERATOR, "Psk_under_generatorZ" }, {FILE_PSK_UNDER_TRANS, "Psk_under_transZ" },
	{FILE_PSTEWARDESS_TROLLEY, "Pstewardess_trolleyZ" }, {FILE_PTESTOBJ, "PtestobjZ" },
	{FILE_PTHUMBPRINTSCANNER, "PthumbprintscannerZ" }, 	 {FILE_PWEAPONCDOOR, "PweaponcdoorZ" },
	{FILE_GCARTBLUE, "GcartblueZ" }, 					 {FILE_GCARTRIDGE, "GcartridgeZ" },
	{FILE_GCARTRIFLE, "GcartrifleZ" }, 					 {FILE_GCARTSHELL, "GcartshellZ" },
	{FILE_GIRSCANNER, "GirscannerZ" }, 					 {FILE_GJOYPAD, "GjoypadZ" }
};

#define EXT_TEX_DIRNAME "/ext_tex"
static char extTexPath[FS_MAXPATH + 1];

#define MAX_EXT_TEX 8192
#define NUM_MODELS_EMBEDDED_TEX ARRAYCOUNT(modelsWithEmbeddedTex)
#define NUM_EMBEDDED_TEX 481


struct ExternalTex
{
	s16 texnum;
	char extension[3];
};

static struct ExternalTex extTextures[MAX_EXT_TEX];
static struct ExternalTex modelExtTextures[NUM_EMBEDDED_TEX];

#if VERSION == VERSION_PAL_FINAL
#define NCHARS 135
#else
#define NCHARS 94
#endif

static struct ExternalTex fontExtTextures[5][NCHARS];

const u8 FONT_HANDELGOTHICSM = 0;
const u8 FONT_HANDELGOTHICMD = 1;
const u8 FONT_HANDELGOTHICXS = 2;
const u8 FONT_HANDELGOTHICLG = 3;
const u8 FONT_NUMERIC = 4;

struct ExtTexEntry fonts[5] = {
	{ FONT_HANDELGOTHICSM, "fonthandelgothicsm" },
	{ FONT_HANDELGOTHICMD, "fonthandelgothicmd" },
	{ FONT_HANDELGOTHICXS, "fonthandelgothicxs" },
	{ FONT_HANDELGOTHICLG, "fonthandelgothiclg" },
	{ FONT_NUMERIC,        "fontnumeric" }
};

s32 modelLookup[NUM_FILES] = { -1 };


s32 fileInfo(const char *filename, s32 *texNum, char extension[3])
{
	char *ext = strrchr(filename, '.');

	// no extension
	if (!ext) return 1;

	++ext;
	extension[0] = ext[0];
	extension[1] = ext[1];
	extension[2] = ext[2];

	// get the filename without extension
	char basename[16] = { 0 };
	memcpy( basename, filename, strlen(filename) - strlen(ext) - 1);
	*texNum = strtol(basename, NULL, 16);
	return 0;
}

struct ExternalTex *lookupModelTex(u16 fileNum, u16 texNum)
{
	if (fileNum > NUM_FILES) {
		sysLogPrintf(LOG_WARNING, "Invalid fileNum in lookupModelTex: %04x, texNum: %04x", fileNum, texNum);
		return 0;
	}

	s16 key = modelLookup[fileNum];
	u16 numTex = (key & 0xf000) >> 12;
	u16 modelOffset = key & 0xfff;

	for (int i = 0; i < numTex; ++i) {
		struct ExternalTex *modelTex = &modelExtTextures[modelOffset + i];
		if (modelTex->texnum == texNum)
			return modelTex;
	}

	return NULL;
}

u8 extTexExists(u8 type, u16 id, u16 texnum)
{
	struct ExternalTex *texlist;
	switch (type) {
		case G_TEXTYPE_NONE:
			return false;
		case G_TEXTYPE_GENERAL:
			texlist = extTextures;
			break;
		case G_TEXTYPE_MODEL:
			return lookupModelTex(id, texnum) != NULL;
		case G_TEXTYPE_FONT:
			texlist = fontExtTextures[id];
			break;
		default:
			sysLogPrintf(LOG_WARNING, "Invalid Texture type: %d, texnum: %04x", type, texnum);
			return false;
	}

	return texlist[texnum].texnum >= 0;
}

u8 *extLoadFontTex(u8 *fontname, s32 idx)
{
	char path[FS_MAXPATH];
	snprintf(path, FS_MAXPATH, "%s/%s/%02X.png", extTexPath, fontname, idx);

	FILE *f = fopen(path, "rb");
	if (!f) {
		fclose(f);
		return NULL;
	}

	s32 width, height, channels;
	u8 *data = stbi_load(path, &width, &height, &channels, 0);
	fclose(f);
	return data;
}

s32 getFileNum(const char *filename)
{
	for (int i = 0; i < NUM_MODELS_EMBEDDED_TEX; ++i) {
		struct ExtTexEntry *item = &modelsWithEmbeddedTex[i];
		if (strcmp(filename, item->name) == 0)
			return item->id;
	}

	sysLogPrintf(LOG_WARNING, "ext_tex::getFileNum unable to resolve filenum for '%s'", filename);
	return -1;
}

const char *getFileName(u16 fileNum)
{
	for (int i = 0; i < NUM_MODELS_EMBEDDED_TEX; ++i) {
		struct ExtTexEntry *item = &modelsWithEmbeddedTex[i];
		if (item->id == fileNum)
			return item->name;
	}

	sysLogPrintf(LOG_WARNING, "ext_tex unable to resolve filename for %04x", fileNum);

	return "";
}

u8 getTexPath(char *dst, u8 type, u16 id, u16 texnum)
{
	struct ExternalTex *tex;
	char *e;
	const char *name;

	switch (type) {
		case G_TEXTYPE_GENERAL: {
			tex = &extTextures[texnum];
			e = tex->extension;
			snprintf(dst, FS_MAXPATH, "%s/%04x.%c%c%c", extTexPath, texnum, e[0], e[1], e[2]);
			return 0;
		}
		case G_TEXTYPE_FONT: {
			name = fonts[id].name;
			tex = &fontExtTextures[id][texnum];
			e = tex->extension;
			snprintf(dst, FS_MAXPATH, "%s/%s/%02x.%c%c%c", extTexPath, name, texnum, e[0], e[1], e[2]);
			return 0;
		}
		case G_TEXTYPE_MODEL: {
			name = getFileName(id);
			tex = lookupModelTex(id, texnum);
			e = tex->extension;
			snprintf(dst, FS_MAXPATH, "%s/%s/%04x.%c%c%c", extTexPath, name, texnum, e[0], e[1], e[2]);
			return 0;
		}
	}

	return 1;
}

u8 *extTexLoad(u8 type, u16 id, u16 texnum, u32 *width, u32 *height)
{
	char path[FS_MAXPATH];
	u8 err = getTexPath(path, type, id, texnum);
	if (err) {
		sysLogPrintf(LOG_WARNING, "Invalid type in extTexLoad: %d, id: 04x, texnum: %04x", type, id, texnum);
		return 0;
	}

	u32 channels;
	return stbi_load(path, width, height, &channels, 0);
}

u8 extTexFontID(struct font *font) {
	if (font == g_FontHandelGothicSm)
		return FONT_HANDELGOTHICSM;
	else if (font == g_FontHandelGothicMd)
		return FONT_HANDELGOTHICMD;
	else if (font == g_FontHandelGothicXs)
		return FONT_HANDELGOTHICXS;
	else if (font == g_FontHandelGothicLg)
		return FONT_HANDELGOTHICLG;
	else if (font == g_FontNumeric)
		return FONT_NUMERIC;

	return 0xff;
}

u8 resolveFontID(const char *fontname)
{
	if (strcmp(fontname, "fonthandelgothicsm") == 0)
		return FONT_HANDELGOTHICSM;
	else if (strcmp(fontname, "fonthandelgothicmd") == 0)
		return FONT_HANDELGOTHICMD;
	else if (strcmp(fontname, "fonthandelgothicxs") == 0)
		return FONT_HANDELGOTHICXS;
	else if (strcmp(fontname, "fonthandelgothiclg") == 0)
		return FONT_HANDELGOTHICLG;
	else if (strcmp(fontname, "fontnumeric") == 0)
		return FONT_NUMERIC;

	return 0xff;
}

void setTex(struct ExternalTex *texlist, s32 index, u16 texNum, char extension[3])
{
	struct ExternalTex *tex = &texlist[index];
	tex->texnum = texNum;
	tex->extension[0] = extension[0];
	tex->extension[1] = extension[1];
	tex->extension[2] = extension[2];
}

void readModelTextures(const char *path, u16 fileNum, s32 *modelOffset)
{
	DIR *dr = opendir(path);
	struct dirent *de;

	s32 numTex = 0;
	char extension[3] = { 0 };
	while ((de = readdir(dr)) != NULL) {
		const char *name = de->d_name;
		if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) continue;

		s32 texNum;
		s32 err = fileInfo(name, &texNum, extension);
		// no extension: skip
		if (err) continue;

		setTex(modelExtTextures, *modelOffset + numTex, texNum, extension);
		numTex++;
	}
	closedir(dr);

	if (numTex > 0) {
		u16 key = (numTex << 12) | *modelOffset;
		modelLookup[fileNum] = key;
		*modelOffset += numTex;
	}
}

void readFontTextures(const char *path, const char *fontName)
{
	DIR *dr = opendir(path);
	struct dirent *de;

	u8 fontID = resolveFontID(fontName);
	char extension[3] = { 0 };
	while ((de = readdir(dr)) != NULL) {
		const char *name = de->d_name;
		if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) continue;

		s32 texNum;
		s32 err = fileInfo(name, &texNum, extension);
		// no extension: skip
		if (err) continue;

		setTex(fontExtTextures[fontID], texNum, texNum, extension);
	}
}

s32 extTexInit()
{
	const char *path = fsFullPath("$B" EXT_TEX_DIRNAME);
	strcpy(extTexPath, path);

	for (int i = 0; i < MAX_EXT_TEX; ++i) {
		extTextures[i].texnum = -1;
	}

	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < NCHARS; ++j)
			fontExtTextures[i][j].texnum = -1;
	}

	struct dirent *de;
	DIR *dr = opendir(extTexPath);

	char filepath[FS_MAXPATH];
	s32 modelOffset = 0;

	char extension[3] = { 0 };
	s32 texNum = 0;
	while ((de = readdir(dr)) != NULL) {
		const char *name = de->d_name;
		if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) continue;

		struct stat stbuf;
		sprintf(filepath , "%s/%s", extTexPath, de->d_name);
		if (stat(filepath, &stbuf) == -1) {
			sysLogPrintf(LOG_NOTE, "Unable to stat file: %s\n", filepath);
			continue;
		}

		// is a directory
		if (S_ISDIR(stbuf.st_mode)) {
			// models
			char s = name[0];
			if (s == 'P' || s == 'C' || s == 'G') {
				s32 fileNum = getFileNum(name);
				if (fileNum < 0) continue;
				modelLookup[fileNum] = modelOffset;
				readModelTextures(filepath, fileNum, &modelOffset);
			}
			// fonts
			else if (s == 'f') {
				readFontTextures(filepath, name);
			}
		} else {
			s32 err = fileInfo(name, &texNum, extension);

			// no extension: skip
			if (err) continue;

			setTex(extTextures, texNum, texNum, extension);
		}
	}

	closedir(dr);
	return 0;
}
