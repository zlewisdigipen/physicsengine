#include "SAT.h"

std::vector<Edge> GetEdges(const std::vector<glm::vec3>& shape)
{
  std::vector<Edge> ret;
  
  for (unsigned i = 0; i < shape.size(); i++)
    ret.push_back(Edge(shape[i], shape[(i + 1) % shape.size()]));

  return ret;
}

std::vector<Triangle> GetFaces(const std::vector<glm::vec3>& shape)
{
  std::vector<Triangle> ret;

  //Check if it is a box or sphere or plane
  if (shape.size() == 4)              //Plane
  {
    ret.push_back(Triangle(shape[0], shape[2], shape[1]));
  }
  else if (shape.size() == 8)         //Box
  {
    ret.push_back(Triangle(shape[0], shape[1], shape[2]));
    ret.push_back(Triangle(shape[4], shape[6], shape[7]));
    ret.push_back(Triangle(shape[6], shape[2], shape[3]));
    ret.push_back(Triangle(shape[0], shape[4], shape[5]));
    ret.push_back(Triangle(shape[6], shape[4], shape[0]));
    ret.push_back(Triangle(shape[3], shape[1], shape[5]));
  }
  else if(shape.size() == 12)         //Sphere
  {
    ret.push_back(Triangle(shape[1], shape[4], shape[0]));
    ret.push_back(Triangle(shape[4], shape[9], shape[0]));
    ret.push_back(Triangle(shape[4], shape[5], shape[9]));
    ret.push_back(Triangle(shape[8], shape[5], shape[4]));
    ret.push_back(Triangle(shape[1], shape[8], shape[4]));
    ret.push_back(Triangle(shape[1], shape[10], shape[8]));
    ret.push_back(Triangle(shape[10], shape[3], shape[8]));
    ret.push_back(Triangle(shape[8], shape[3], shape[5]));
    ret.push_back(Triangle(shape[3], shape[2], shape[5]));
    ret.push_back(Triangle(shape[3], shape[7], shape[2]));
    ret.push_back(Triangle(shape[3], shape[10], shape[7]));
    ret.push_back(Triangle(shape[10], shape[6], shape[7]));
    ret.push_back(Triangle(shape[6], shape[11], shape[7]));
    ret.push_back(Triangle(shape[6], shape[0], shape[11]));
    ret.push_back(Triangle(shape[6], shape[1], shape[0]));
    ret.push_back(Triangle(shape[10], shape[1], shape[6]));
    ret.push_back(Triangle(shape[11], shape[0], shape[9]));
    ret.push_back(Triangle(shape[2], shape[11], shape[9]));
    ret.push_back(Triangle(shape[5], shape[2], shape[9]));
    ret.push_back(Triangle(shape[11], shape[2], shape[7]));
  }

  return ret;
}

glm::vec3 FarthestPoint(const std::vector<glm::vec3>& shape, const glm::vec3& direction)
{
  float furthest = glm::dot(shape[0], direction);
  unsigned index = 0;

  for (unsigned i = 0; i < shape.size(); i++)
  {
    float check = glm::dot(shape[i], direction);

    if (check > furthest)
    {
      furthest = check;
      index = i;
    }
  }

  return shape[index];
}

Query QueryFaceDirections(const std::vector<Triangle>& tri, const std::vector<glm::vec3>& shape)
{
  float best_dist = std::numeric_limits<float>::lowest();
  unsigned best_ind = 0;

  for (unsigned i = 0; i < tri.size(); i++)
  {
    //Get farthest point in given direction and distance to that point
    glm::vec3 vertex_b = FarthestPoint(shape, -tri[i].crs);
    float dist = glm::dot(tri[i].crs, (vertex_b - tri[i].points[0]));

    if (dist > best_dist)
    {
      best_dist = dist;
      best_ind = i;
    }

    if (best_dist > 0.0f)
      break;
  }

  //Build and return query
  Query ret;
  ret.using_face = true;
  ret.seperation = best_dist;
  ret.face_ind = best_ind;
  return ret;
}

Interval IntervalProjection(const std::vector<glm::vec3>& shape, glm::vec3 axis)
{
  Interval ret;

  ret.min = glm::dot(shape[0], axis);
  ret.max = glm::dot(shape[0], axis);

  for (unsigned i = 1; i < shape.size(); i++)
  {
    float d = glm::dot(shape[i], axis);
    if (d < ret.min)
      ret.min = d;
    else if (d > ret.max)
      ret.max = d;
  }

  return ret;
}

Query QueryEdgeDirections(const std::vector<glm::vec3>& shape_a, const std::vector<glm::vec3>& shape_b)
{
  std::vector<Edge> edge1 = GetEdges(shape_a);
  std::vector<Edge> edge2 = GetEdges(shape_b);
  bool early_out = false;
  float best_dist = std::numeric_limits<float>::lowest();;
  unsigned e1, e2;

  for (unsigned i = 0; i < edge1.size(); i++)
  {
    for (unsigned j = 0; j < edge2.size(); j++)
    {
      glm::vec3 axis = glm::cross(edge1[i].direction, edge2[j].direction);

      Interval interval1 = IntervalProjection(shape_a, axis);
      Interval interval2 = IntervalProjection(shape_b, axis);
      float dist = glm::max(interval1.min - interval2.max, interval2.min - interval1.max);

      if (dist > best_dist)
      {
        best_dist = dist;
        e1 = i;
        e2 = j;
      }

      if (best_dist > 0.0f)
        early_out = true;
    }

    if (early_out)
      break;
  }

  Query ret;
  ret.using_face = false;
  ret.seperation = best_dist;
  ret.edge1_ind = e1;
  ret.edge2_ind = e2;
  return ret;
}

bool OverLap(const std::vector<glm::vec3>& shape_a, const std::vector<glm::vec3>& shape_b, glm::vec3& normal)
{
  std::vector<Triangle> f_a = GetFaces(shape_a);
  Query q_a = QueryFaceDirections(f_a, shape_b); //Face normals of A
  if (q_a.seperation > 0.0f)
    return false;

  std::vector<Triangle> f_b = GetFaces(shape_b);
  Query q_b = QueryFaceDirections(f_b, shape_a); //Face normals of B
  if (q_b.seperation > 0.0f)
    return false;

  Query q_e = QueryEdgeDirections(shape_a, shape_b); //Edge test
  if (q_e.seperation > 0.0f)
    return false;

  //Implement Clipping
  if (q_e.seperation < 0.0f)
  {
    normal = -glm::vec3(0.0f, 1.0f, 0.0f);
    return true;
  }

  if (q_a.seperation <= q_b.seperation)
    normal = f_a[q_a.face_ind].crs;
  else
    normal = f_b[q_b.face_ind].crs;


  return true;
}
