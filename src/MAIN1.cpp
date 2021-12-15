#include "H01_Platform.h"
#include <stdio.h>

MOTION_FOR_GXD testMot;
SOBJECT_FOR_GXD testSob;

void MAIN::Logic1( float dTime )
{
}

void MAIN::Draw1( float dTime )
{
    if( !testMot.mCheckValidState )
    {
		printf( "Load Motion = %d\n", testMot.Load( "E:/offzip/C001001002.MOTION.out/00000008.dat" ) );
    }
	if ( !testSob.mCheckValidState )
	{
		printf( "Load Sobject = %d\n", testSob.Load("E:/offzip/C001003000.SOBJECT.out/00000010.neo", TRUE, TRUE ) );
	}
	
	float tL[3] = { 0.0f, 0.0f, 0.0f };
	float tA[3] = { 0.0f, 0.0f, 0.0f };
	testSob.DrawForSelect( 0, 1.0f, tL, tA, &testMot, 20.0f );

    //if (IsFileDropped())
    //{
    //    int count = 0;
    //    char** droppedFiles = GetDroppedFiles(&count);
    //
    //    if (count == 1) // Only support one file dropped
    //    {
    //        if (IsFileExtension(droppedFiles[0], ".obj") ||
    //            IsFileExtension(droppedFiles[0], ".gltf") ||
    //            IsFileExtension(droppedFiles[0], ".glb") ||
    //            IsFileExtension(droppedFiles[0], ".vox") ||
    //            IsFileExtension(droppedFiles[0], ".iqm"))       // Model file formats supported
    //        {
    //            UnloadModel(model);                     // Unload previous model
    //            model = LoadModel(droppedFiles[0]);     // Load new model
    //            model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture; // Set current map diffuse texture
    //
    //            // TODO: Move camera position from target enough distance to visualize model properly
    //        }
    //        else if (
    //            IsFileExtension(droppedFiles[0], ".png") ||
    //            IsFileExtension(droppedFiles[0], ".dds")
    //            )  // Texture file formats supported
    //        {
    //            // Unload current model texture and load new one
    //            UnloadTexture(texture);
    //            texture = LoadTexture(droppedFiles[0]);
    //            texture.mipmaps = 0;
    //            model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    //        }
    //        
    //    }
    //
    //    ClearDroppedFiles();    // Clear internal buffers
    //}
    //
    //DrawModel(model, position, 1.0f, WHITE);        // Draw 3d model with texture
}
