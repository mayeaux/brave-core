/* Copyright 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "build/build_config.h"

// Disable InterestFeedContentSuggestions on Android.
#if defined(OS_ANDROID)
#include "components/feed/feed_feature_list.h"

#define kInterestFeedContentSuggestions \
  kInterestFeedContentSuggestions_Chromium

#include "../../../../components/feed/feed_feature_list.cc"

#undef kInterestFeedContentSuggestions

namespace feed {

const base::Feature kInterestFeedContentSuggestions{
    "InterestFeedContentSuggestions", base::FEATURE_DISABLED_BY_DEFAULT};

}
#else
#include "../../../../components/feed/feed_feature_list.cc"
#endif  // defined(OS_ANDROID)
