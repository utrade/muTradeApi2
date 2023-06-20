#pragma once

#include <sgContext.h>
#include <sharedCommands.h>
#include <orderWrapperAPI.h>

namespace API2
{
  namespace COMMON
  {
    using OrderWrapper = ::API2::COMMON::OrderWrapperAPI;
  }
}

typedef API2::COMMON::OrderWrapper OrderWrapper;
