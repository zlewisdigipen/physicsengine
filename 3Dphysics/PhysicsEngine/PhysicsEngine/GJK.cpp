#include "GJK.h"

//Can add extra checks to make the process go faster
//In Simplex4 instead of just leaving with triangle, I can just do a faster simplex3 check

void Simplex2(std::vector<glm::vec3>& simplex, glm::vec3& dir)
{
  //easier to read stuff
  glm::vec3 ab = simplex[0] - simplex[1];
  glm::vec3 ao = -simplex[1];

  if (glm::dot(ab, ao) > 0.0f)
    //AB x AO x AB
    dir = glm::cross(glm::cross(ab, ao), ab);
  else
  {
    simplex.erase(simplex.begin());
    dir = ao;
  }
}

void Simplex3(std::vector<glm::vec3>& simplex, glm::vec3& dir)
{
  //normal of triangle and easier to read stuff
  glm::vec3 abc = glm::cross(simplex[1] - simplex[2], simplex[0] - simplex[2]);
  glm::vec3 ab = simplex[1] - simplex[2];
  glm::vec3 ac = simplex[0] - simplex[2];
  glm::vec3 ao = -simplex[2];

  //Closest edge is AB
  if (glm::dot(glm::cross(ab, abc), ao) > 0) 
  {
    //Get rid of C
    simplex.erase(simplex.begin());
    dir = glm::cross(glm::cross(ab, ao), ab);
    return;
  }

  //Closest to edge AC
  if (glm::dot(glm::cross(abc, ac), ao) > 0) 
  { 
    //Get rid of B
    simplex.erase(simplex.begin() + 1);
    dir = glm::cross(glm::cross(ac, ao), ac);
    return;
  }

  //Above triangle
  if (glm::dot(abc, ao) > 0) 
  { 
    //simp_dim = 3;
    dir = abc;
  }
  else
  {
    //Below triangle
    //Swap B and C
    glm::vec3 temp = simplex[0];
    simplex[0] = simplex[1];
    simplex[1] = temp;
    dir = --abc;
  }
}

bool Simplex4(std::vector<glm::vec3>& simplex, glm::vec3& dir)
{
  //0 = D, 1 = C, 2 = B, 3 = A
  //Check first triangle
  glm::vec3 abc = glm::cross(simplex[2] - simplex[3], simplex[1] - simplex[3]);
  glm::vec3 ao = -simplex[3];

  if (glm::dot(abc, ao) > 0.0f)
  {
    //new simplex without D
    simplex.erase(simplex.begin());
    dir = abc;
    //Simplex3(simplex, dir);
    return false;
  }

  //Check 2nd triangle
  glm::vec3 acd = glm::cross(simplex[1] - simplex[3], simplex[0] - simplex[3]);

  if (glm::dot(acd, ao) > 0.0f)
  {
    //new simplex without B
    simplex.erase(simplex.begin() + 2);
    dir = acd;
    //Simplex3(simplex, dir);
    return false;
  }

  //Check 3rd triangle
  glm::vec3 adb = glm::cross(simplex[0] - simplex[3], simplex[2] - simplex[3]);

  if (glm::dot(adb, ao) > 0.0f)
  {
    //new simplex without C and swap B and D
    simplex[1] = simplex[2];
    simplex[2] = simplex[0];
    simplex.erase(simplex.begin());

    dir = adb;
    //Simplex3(simplex, dir);
    return false;
  }

  //This means that the origin is in the tetrahedron
  return true;
}

bool ContainsOrigin(std::vector<glm::vec3>& simplex, glm::vec3& dir)
{
  //Different things for different sizes
  if (simplex.size() == 2)                           //line
    Simplex2(simplex, dir);
  else if (simplex.size() == 3)                      //Triangle
    Simplex3(simplex, dir);
  else if (simplex.size() == 4)                      //Tetrahedron
    return Simplex4(simplex, dir);

  return false;
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


bool GJK_Intersection(const std::vector<glm::vec3>& shape_a, const std::vector<glm::vec3>& shape_b, glm::vec3& direction, std::vector<glm::vec3>& simplex)
{
  glm::vec3 a = FarthestPoint(shape_a, direction) - FarthestPoint(shape_b, -direction);
  simplex.push_back(a);
  direction = -a;

  //Finding collision
  while (1)
  {
    a = FarthestPoint(shape_a, direction) - FarthestPoint(shape_b, -direction);

    //Check if point passed origin
    if (glm::dot(a, direction) < 0)
      return false;

    simplex.push_back(a);

    //Check if simplex contains origin
    if (ContainsOrigin(simplex, direction))
      return true;
  }

  return true;
}
