//============== FOR GRID ==============================//
bool grid2DMode = false;
uint gridSize = 16;
uint gridSubdivisions = 3;
float gridScale = 8.0;
Color gridColor(0.5, 0.5, 0.5);
Color gridSubdivisionColor(0.5, 0.5, 0.5);
Color gridXColor(0.5, 0.1, 0.1);
Color gridYColor(0.1, 0.5, 0.1);
Color gridZColor(0.1, 0.1, 0.5);
//============== FOR GRID ==============================//


void CreateGrid()
{
    Node@ gridNode = scene_.CreateChild("Grid");
    CustomGeometry@ grid = gridNode.CreateComponent("CustomGeometry");
    grid.numGeometries = 1;
    grid.material = cache.GetResource("Material", "Materials/VColUnlit.xml");
    grid.viewMask = 0x80000000; // Editor raycasts use viewmask 0x7fffffff
    grid.occludee = false;

    UpdateGrid();
}

void UpdateGrid(bool updateGridGeometry = true)
{
    float gridScale = 8.0;
    Node@ gridNode = scene_.GetChild("Grid");
    gridNode.scale = Vector3(gridScale, gridScale, gridScale);

    if (!updateGridGeometry)
        return;

    CustomGeometry@ grid = gridNode.GetComponent("CustomGeometry");

    uint size = uint(Floor(gridSize / 2) * 2);
    float halfSizeScaled = size / 2;
    float scale = 1.0;
    uint subdivisionSize = uint(Pow(2.0f, float(gridSubdivisions)));

    if (subdivisionSize > 0)
    {
        size *= subdivisionSize;
        scale /= subdivisionSize;
    }

    uint halfSize = size / 2;

    grid.BeginGeometry(0, LINE_LIST);
    float lineOffset = -halfSizeScaled;
    for (uint i = 0; i <= size; ++i)
    {
        bool lineCenter = i == halfSize;
        bool lineSubdiv = !Equals(Mod(i, subdivisionSize), 0.0);

        if (!grid2DMode)
        {
            grid.DefineVertex(Vector3(lineOffset, 0.0, halfSizeScaled));
            grid.DefineColor(lineCenter ? gridZColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
            grid.DefineVertex(Vector3(lineOffset, 0.0, -halfSizeScaled));
            grid.DefineColor(lineCenter ? gridZColor : (lineSubdiv ? gridSubdivisionColor : gridColor));

            grid.DefineVertex(Vector3(-halfSizeScaled, 0.0, lineOffset));
            grid.DefineColor(lineCenter ? gridXColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
            grid.DefineVertex(Vector3(halfSizeScaled, 0.0, lineOffset));
            grid.DefineColor(lineCenter ? gridXColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
        }
        else
        {
            grid.DefineVertex(Vector3(lineOffset, halfSizeScaled, 0.0));
            grid.DefineColor(lineCenter ? gridYColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
            grid.DefineVertex(Vector3(lineOffset, -halfSizeScaled, 0.0));
            grid.DefineColor(lineCenter ? gridYColor : (lineSubdiv ? gridSubdivisionColor : gridColor));

            grid.DefineVertex(Vector3(-halfSizeScaled, lineOffset, 0.0));
            grid.DefineColor(lineCenter ? gridXColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
            grid.DefineVertex(Vector3(halfSizeScaled, lineOffset, 0.0));
            grid.DefineColor(lineCenter ? gridXColor : (lineSubdiv ? gridSubdivisionColor : gridColor));
        }

        lineOffset  += scale;
    }
    grid.Commit();
}