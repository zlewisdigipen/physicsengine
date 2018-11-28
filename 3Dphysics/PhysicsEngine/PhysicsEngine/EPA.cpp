#include "EPA.h"
#include "GJK.h"

glm::vec3 EPA(const std::vector<glm::vec3>& shape_a, const std::vector<glm::vec3>& shape_b, std::vector<glm::vec3>& poly)
{
  //D = 0, C = 1, B = 2, A = 3
  //Build triangles
  std::vector<Triangle> tri_ls;
  tri_ls.push_back(Triangle(poly[3], poly[2], poly[1])); //ABC
  tri_ls.push_back(Triangle(poly[3], poly[1], poly[0])); //ACD
  tri_ls.push_back(Triangle(poly[3], poly[0], poly[2])); //ADB
  tri_ls.push_back(Triangle(poly[2], poly[0], poly[1])); //BDC

  while (1)
  {
    unsigned c_in = 0;
    float min_dist = std::abs(glm::dot(-tri_ls[0].points[0], tri_ls[0].crs));

    //Find closest face to origin
    for (unsigned i = 1; i < tri_ls.size(); i++)
    {
      float dist = std::abs(glm::dot(-tri_ls[i].points[0], tri_ls[i].crs));
      if (dist < min_dist)
      {
        min_dist = dist;
        c_in = i;
      }
    }

    //Using normal find furthest point
    glm::vec3 dir = tri_ls[c_in].crs;
    glm::vec3 p = FarthestPoint(shape_a, dir) - FarthestPoint(shape_b, -dir);

    //Check if point is on edge and return penatration vector
    if (glm::dot(p, dir) - min_dist < 0.0001f)
      return tri_ls[c_in].crs * glm::dot(p, dir);

    std::vector<Edge> edges;

    for (int i = 0; i < tri_ls.size(); i++)
    {
      //Check if face is facing p and remove face
      if (glm::dot(tri_ls[i].crs, p) > 0)
      {
        //Check and add faces edges to list
        for (unsigned j = 0; j < 3; j++)
        {
          Edge e(tri_ls[i].points[j], tri_ls[i].points[(j+1)%3]);
          bool add = true;

          //Check reverse order if edges in list
          for (unsigned k = 0; k < edges.size(); k++)
          {
            if (e.points[0] == edges[k].points[1] && e.points[1] == edges[k].points[0])
            {
              //Remove edge from edges
              edges.erase(edges.begin() + k);
              add = false;
              break; //Found edge, don't need to continue
            }
          }
          
          //Add the new edge
          if (add)
            edges.push_back(e);
        }

        //Remove face
        tri_ls.erase(tri_ls.begin() + i);
        i--;
      }
    }

    //Adding triangles
    for (unsigned i = 0; i < edges.size(); i++)
      tri_ls.push_back(Triangle(edges[i].points[0], edges[i].points[1], p));
  }
}
