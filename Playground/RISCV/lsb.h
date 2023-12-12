#pragma once
#include "utility.h"

namespace dark {

struct load_store_buffer {
  public:
    wire wrFlag;        // Whether to write.
    wire dataIn;        // Data to store.

  public:
    reg  update;        // Whether to update the value
    reg  updateRob;     // RobIndex of the update
    reg  updateVal;     // Value to update with

    reg  dataOut;       // Data to store.




};



} // namespace dark
