#include "dynamic_voxel.h"
#include "StarlabDrawArea.h"

void dynamic_voxel::decorate()
{
    if(showVoxels)
        vox.draw();
}

void dynamic_voxel::create(){

    showMesh = false;
    showVoxels = false;

    drawArea()->updateGL();
}

bool dynamic_voxel::keyPressEvent( QKeyEvent* event )
{
    bool used = false;

    if(event->key() == Qt::Key_V) {
        showVoxels = !showVoxels;

		Vec3d to(2,2,0);
		double radius = 0.5;

		vox.begin();

		QVector<Vec3d> points;
		points.push_back(Vec3d(-1,-1,0));
		points.push_back(Vec3d(0,-1,0));
		points.push_back(Vec3d(0,0,0));
		points.push_back(Vec3d(1,0,0));
		points.push_back(Vec3d(1,1,0));
		points.push_back(Vec3d(2,1,0));
		points.push_back(Vec3d(2,2,0));
		vox.addPolyLine(points, radius);

		vox.end();

        used = true;
    }

    if(event->key() == Qt::Key_M) {
        showMesh = !showMesh;

		SurfaceMesh::Model * m = new SurfaceMesh::Model("voxel_example.obj", "voxel");
		vox.buildMesh( m );
		vox.MeanCurvatureFlow( m );
		document()->addModel(m);

        used = true;
    }

    drawArea()->updateGL();

    return used;
}

Q_EXPORT_PLUGIN (dynamic_voxel)