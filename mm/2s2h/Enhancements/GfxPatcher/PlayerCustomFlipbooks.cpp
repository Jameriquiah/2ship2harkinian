#include "PlayerCustomFlipbooks.h"
#include "2s2h/BenPort.h"

#include <array>
#include <string>

extern "C" {
#include "z64player.h"
extern TexturePtr sPlayerEyesTextures[PLAYER_FORM_MAX][PLAYER_EYES_MAX];
extern TexturePtr sPlayerMouthTextures[PLAYER_FORM_MAX][PLAYER_MOUTH_MAX];
uint8_t ResourceMgr_FileExists(const char* resName);
bool ResourceMgr_IsAltAssetsEnabled();
}

#ifdef __ANDROID__
#define ALIGNED_OTR_PATH(name, value) alignas(2) static const char name[] = value

ALIGNED_OTR_PATH(sFDEyesOpenTex, "__OTR__objects/object_link_boy/gLinkFierceDeityEyesOpenTex");
ALIGNED_OTR_PATH(sFDEyesHalfTex, "__OTR__objects/object_link_boy/gLinkFierceDeityEyesHalfTex");
ALIGNED_OTR_PATH(sFDEyesClosedTex, "__OTR__objects/object_link_boy/gLinkFierceDeityEyesClosedTex");
ALIGNED_OTR_PATH(sFDEyesRightTex, "__OTR__objects/object_link_boy/gLinkFierceDeityEyesRightTex");
ALIGNED_OTR_PATH(sFDEyesLeftTex, "__OTR__objects/object_link_boy/gLinkFierceDeityEyesLeftTex");
ALIGNED_OTR_PATH(sFDEyesUpTex, "__OTR__objects/object_link_boy/gLinkFierceDeityEyesUpTex");
ALIGNED_OTR_PATH(sFDEyesDownTex, "__OTR__objects/object_link_boy/gLinkFierceDeityEyesDownTex");
ALIGNED_OTR_PATH(sFDEyesWincingTex, "__OTR__objects/object_link_boy/gLinkFierceDeityEyesWincingTex");

ALIGNED_OTR_PATH(sFDMouthClosedTex, "__OTR__objects/object_link_boy/gLinkFierceDeityMouthClosedTex");
ALIGNED_OTR_PATH(sFDMouthHalfTex, "__OTR__objects/object_link_boy/gLinkFierceDeityMouthHalfTex");
ALIGNED_OTR_PATH(sFDMouthOpenTex, "__OTR__objects/object_link_boy/gLinkFierceDeityMouthOpenTex");
ALIGNED_OTR_PATH(sFDMouthSmileTex, "__OTR__objects/object_link_boy/gLinkFierceDeityMouthSmileTex");

ALIGNED_OTR_PATH(sDekuEyesOpenTex, "__OTR__objects/object_link_nuts/gLinkDekuEyesOpenTex");
ALIGNED_OTR_PATH(sDekuEyesHalfTex, "__OTR__objects/object_link_nuts/gLinkDekuEyesHalfTex");
ALIGNED_OTR_PATH(sDekuEyesClosedTex, "__OTR__objects/object_link_nuts/gLinkDekuEyesClosedTex");
ALIGNED_OTR_PATH(sDekuEyesRightTex, "__OTR__objects/object_link_nuts/gLinkDekuEyesRightTex");
ALIGNED_OTR_PATH(sDekuEyesLeftTex, "__OTR__objects/object_link_nuts/gLinkDekuEyesLeftTex");
ALIGNED_OTR_PATH(sDekuEyesUpTex, "__OTR__objects/object_link_nuts/gLinkDekuEyesUpTex");
ALIGNED_OTR_PATH(sDekuEyesDownTex, "__OTR__objects/object_link_nuts/gLinkDekuEyesDownTex");
ALIGNED_OTR_PATH(sDekuEyesWincingTex, "__OTR__objects/object_link_nuts/gLinkDekuEyesWincingTex");

ALIGNED_OTR_PATH(sDekuMouthClosedTex, "__OTR__objects/object_link_nuts/gLinkDekuMouthClosedTex");
ALIGNED_OTR_PATH(sDekuMouthHalfTex, "__OTR__objects/object_link_nuts/gLinkDekuMouthHalfTex");
ALIGNED_OTR_PATH(sDekuMouthOpenTex, "__OTR__objects/object_link_nuts/gLinkDekuMouthOpenTex");
ALIGNED_OTR_PATH(sDekuMouthSmileTex, "__OTR__objects/object_link_nuts/gLinkDekuMouthSmileTex");

ALIGNED_OTR_PATH(sGoronMouthClosedTex, "__OTR__objects/object_link_goron/gLinkGoronMouthClosedTex");
ALIGNED_OTR_PATH(sGoronMouthHalfTex, "__OTR__objects/object_link_goron/gLinkGoronMouthHalfTex");
ALIGNED_OTR_PATH(sGoronMouthOpenTex, "__OTR__objects/object_link_goron/gLinkGoronMouthOpenTex");
ALIGNED_OTR_PATH(sGoronMouthSmileTex, "__OTR__objects/object_link_goron/gLinkGoronMouthSmileTex");

static const char* sFDEyesTextures[PLAYER_EYES_MAX] = {
    sFDEyesOpenTex,
    sFDEyesHalfTex,
    sFDEyesClosedTex,
    sFDEyesRightTex,
    sFDEyesLeftTex,
    sFDEyesUpTex,
    sFDEyesDownTex,
    sFDEyesWincingTex,
};

static const char* sFDMouthTextures[PLAYER_MOUTH_MAX] = {
    sFDMouthClosedTex,
    sFDMouthHalfTex,
    sFDMouthOpenTex,
    sFDMouthSmileTex,
};

static const char* sDekuEyesTextures[PLAYER_EYES_MAX] = {
    sDekuEyesOpenTex,   sDekuEyesHalfTex,
    sDekuEyesClosedTex, sDekuEyesRightTex,
    sDekuEyesLeftTex,   sDekuEyesUpTex,
    sDekuEyesDownTex,   sDekuEyesWincingTex,
};

static const char* sDekuMouthTextures[PLAYER_MOUTH_MAX] = {
    sDekuMouthClosedTex,
    sDekuMouthHalfTex,
    sDekuMouthOpenTex,
    sDekuMouthSmileTex,
};

static const char* sGoronMouthTextures[PLAYER_MOUTH_MAX] = {
    sGoronMouthClosedTex,
    sGoronMouthHalfTex,
    sGoronMouthOpenTex,
    sGoronMouthSmileTex,
};

#undef ALIGNED_OTR_PATH
#else
static const char* sFDEyesTextures[PLAYER_EYES_MAX] = {
    "__OTR__objects/object_link_boy/gLinkFierceDeityEyesOpenTex",
    "__OTR__objects/object_link_boy/gLinkFierceDeityEyesHalfTex",
    "__OTR__objects/object_link_boy/gLinkFierceDeityEyesClosedTex",
    "__OTR__objects/object_link_boy/gLinkFierceDeityEyesRightTex",
    "__OTR__objects/object_link_boy/gLinkFierceDeityEyesLeftTex",
    "__OTR__objects/object_link_boy/gLinkFierceDeityEyesUpTex",
    "__OTR__objects/object_link_boy/gLinkFierceDeityEyesDownTex",
    "__OTR__objects/object_link_boy/gLinkFierceDeityEyesWincingTex",
};

static const char* sFDMouthTextures[PLAYER_MOUTH_MAX] = {
    "__OTR__objects/object_link_boy/gLinkFierceDeityMouthClosedTex",
    "__OTR__objects/object_link_boy/gLinkFierceDeityMouthHalfTex",
    "__OTR__objects/object_link_boy/gLinkFierceDeityMouthOpenTex",
    "__OTR__objects/object_link_boy/gLinkFierceDeityMouthSmileTex",
};

static const char* sDekuEyesTextures[PLAYER_EYES_MAX] = {
    "__OTR__objects/object_link_nuts/gLinkDekuEyesOpenTex",   "__OTR__objects/object_link_nuts/gLinkDekuEyesHalfTex",
    "__OTR__objects/object_link_nuts/gLinkDekuEyesClosedTex", "__OTR__objects/object_link_nuts/gLinkDekuEyesRightTex",
    "__OTR__objects/object_link_nuts/gLinkDekuEyesLeftTex",   "__OTR__objects/object_link_nuts/gLinkDekuEyesUpTex",
    "__OTR__objects/object_link_nuts/gLinkDekuEyesDownTex",   "__OTR__objects/object_link_nuts/gLinkDekuEyesWincingTex",
};

static const char* sDekuMouthTextures[PLAYER_MOUTH_MAX] = {
    "__OTR__objects/object_link_nuts/gLinkDekuMouthClosedTex",
    "__OTR__objects/object_link_nuts/gLinkDekuMouthHalfTex",
    "__OTR__objects/object_link_nuts/gLinkDekuMouthOpenTex",
    "__OTR__objects/object_link_nuts/gLinkDekuMouthSmileTex",
};

static const char* sGoronMouthTextures[PLAYER_MOUTH_MAX] = {
    "__OTR__objects/object_link_goron/gLinkGoronMouthClosedTex",
    "__OTR__objects/object_link_goron/gLinkGoronMouthHalfTex",
    "__OTR__objects/object_link_goron/gLinkGoronMouthOpenTex",
    "__OTR__objects/object_link_goron/gLinkGoronMouthSmileTex",
};
#endif

static std::array<std::string, PLAYER_EYES_MAX> sResolvedFDEyesTextures;
static std::array<std::string, PLAYER_MOUTH_MAX> sResolvedFDMouthTextures;
static std::array<std::string, PLAYER_EYES_MAX> sResolvedDekuEyesTextures;
static std::array<std::string, PLAYER_MOUTH_MAX> sResolvedDekuMouthTextures;
static std::array<std::string, PLAYER_MOUTH_MAX> sResolvedGoronMouthTextures;

static s32 sFacePatchAltState = -1;

static bool ResolveTexturePath(const char* basePath, std::string& resolvedPath) {
    std::string resourcePath = basePath;
    if (resourcePath.starts_with("__OTR__")) {
        resourcePath = resourcePath.substr(7);
    }

    if (ResourceMgr_IsAltAssetsEnabled()) {
        const std::string altPath = "__OTR__alt/" + resourcePath;
        if (ResourceMgr_FileExists(altPath.c_str())) {
            resolvedPath = altPath;
            return true;
        }
    }

    if (ResourceMgr_FileExists(basePath)) {
        resolvedPath = basePath;
        return true;
    }

    return false;
}

template <size_t Count>
static bool ResolveTextureSet(const char* const (&sourcePaths)[Count], std::array<std::string, Count>& resolvedPaths) {
    for (size_t i = 0; i < Count; i++) {
        if (!ResolveTexturePath(sourcePaths[i], resolvedPaths[i])) {
            return false;
        }
    }

    return true;
}

static void ApplyEyesTextureSet(s32 form, const std::array<std::string, PLAYER_EYES_MAX>& resolvedPaths) {
    for (s32 i = 0; i < PLAYER_EYES_MAX; i++) {
        sPlayerEyesTextures[form][i] = (TexturePtr)resolvedPaths[i].c_str();
    }
}

static void ApplyMouthTextureSet(s32 form, const std::array<std::string, PLAYER_MOUTH_MAX>& resolvedPaths) {
    for (s32 i = 0; i < PLAYER_MOUTH_MAX; i++) {
        sPlayerMouthTextures[form][i] = (TexturePtr)resolvedPaths[i].c_str();
    }
}

void PlayerCustomFlipbooks_Patch(void) {
    const s32 altState = ResourceMgr_IsAltAssetsEnabled() ? 1 : 0;
    if (sFacePatchAltState == altState) {
        return;
    }

    sFacePatchAltState = altState;

    if (ResolveTextureSet(sFDEyesTextures, sResolvedFDEyesTextures)) {
        ApplyEyesTextureSet(PLAYER_FORM_FIERCE_DEITY, sResolvedFDEyesTextures);
    }

    if (ResolveTextureSet(sFDMouthTextures, sResolvedFDMouthTextures)) {
        ApplyMouthTextureSet(PLAYER_FORM_FIERCE_DEITY, sResolvedFDMouthTextures);
    }

    if (ResolveTextureSet(sDekuEyesTextures, sResolvedDekuEyesTextures)) {
        ApplyEyesTextureSet(PLAYER_FORM_DEKU, sResolvedDekuEyesTextures);
    }

    if (ResolveTextureSet(sDekuMouthTextures, sResolvedDekuMouthTextures)) {
        ApplyMouthTextureSet(PLAYER_FORM_DEKU, sResolvedDekuMouthTextures);
    }

    if (ResolveTextureSet(sGoronMouthTextures, sResolvedGoronMouthTextures)) {
        ApplyMouthTextureSet(PLAYER_FORM_GORON, sResolvedGoronMouthTextures);
    }
}
