#include "undeleted_example.hpp"
#include "untracked_example.hpp"
#include "deleted_example.hpp"
#include "missingVirtualDestructor_example.hpp"
#include "undeletedArray_example.hpp"
#include "deletedArray_example.hpp"

#include <iostream>

int main()
{
  std::cout << std::endl;

  std::cout << "Deleted Example - ";
  deletedExample();

  std::cout << "Undeleted Example - ";
  undeletedExample();

  std::cout << "Missing Virtual Destructor Example - ";
  missingVirtualDestructorExample();

  std::cout << "Untracked Example - ";
  untrackedExample();

  std::cout << "Undeleted Array Example - ";
  undeletedArrayExample();

  std::cout << "Deleted Array Example - ";
  deletedArrayExample();

  std::cout << std::endl;
}