#include "StdAfx.h"
#include "Scene.h"

#include "Mesh.h"
#include "Light.h"
#include "SceneLoader.h"

#include "Engine.h"
#include "VM.h"
#include "Renderer.h"
#include "FileSystem.h"

CScene::CScene(LPCSTR modelPath)
{
    mRootNode = NULL;

    if (modelPath)
        LoadScene(modelPath);
}

VOID CScene::Release()
{
    if (DelRef())
    {
        SAFE_RELEASE(mRootNode);

        mMeshes.Release();
        mLights.Release();
        mNodes.Release();

        delete this;
    }
}

BOOL CScene::LoadScene(LPCSTR modelPath, BOOL loadMaterials, BOOL optimizeMesh)
{
    BOOL ok = CSceneLoader::LoadScene(modelPath, this, loadMaterials, optimizeMesh);

    if (!ok)
    {
        VM->PostError(std::string("Could not load model file: ") + modelPath);
        return FALSE;
    }

    mRootNode = mNodes[0];
    return TRUE;
}

