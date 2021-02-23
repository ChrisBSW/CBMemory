#include "undeleted_example.hpp"
#include "untracked_example.hpp"
#include "deleted_example.hpp"
#include "missingVirtualDestructor_example.hpp"

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
  std::cout << std::endl;
}