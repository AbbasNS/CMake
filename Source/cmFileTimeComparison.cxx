/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#include "cmFileTimeComparison.h"

#include <string>
#include <unordered_map>
#include <utility>

cmFileTimeComparison::cmFileTimeComparison() = default;

cmFileTimeComparison::~cmFileTimeComparison() = default;

bool cmFileTimeComparison::Load(std::string const& fileName,
                                cmFileTime& fileTime)
{
  // Use the stored time if available.
  {
    auto fit = this->FileTimes.find(fileName);
    if (fit != this->FileTimes.end()) {
      fileTime = fit->second;
      return true;
    }
  }
  // Read file time from OS
  if (!fileTime.Load(fileName)) {
    return false;
  }
  // Store file time in cache
  this->FileTimes[fileName] = fileTime;
  return true;
}

bool cmFileTimeComparison::FileTimeCompare(std::string const& f1,
                                           std::string const& f2, int* result)
{
  // Get the modification time for each file.
  cmFileTime ft1, ft2;
  if (this->Load(f1, ft1) && this->Load(f2, ft2)) {
    // Compare the two modification times.
    *result = ft1.Compare(ft2);
    return true;
  }
  // No comparison available.  Default to the same time.
  *result = 0;
  return false;
}

bool cmFileTimeComparison::FileTimesDiffer(std::string const& f1,
                                           std::string const& f2)
{
  // Get the modification time for each file.
  cmFileTime ft1, ft2;
  if (this->Load(f1, ft1) && this->Load(f2, ft2)) {
    // Compare the two modification times.
    return ft1.DifferS(ft2);
  }
  // No comparison available.  Default to different times.
  return true;
}
