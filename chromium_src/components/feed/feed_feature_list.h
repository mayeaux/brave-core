/* Copyright 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_CHROMIUM_SRC_COMPONENTS_FEED_FEED_FEATURE_LIST_H_
#define BRAVE_CHROMIUM_SRC_COMPONENTS_FEED_FEED_FEATURE_LIST_H_

#include "build/build_config.h"
#include "../../../../components/feed/feed_feature_list.h"
#if defined(OS_ANDROID)
namespace feed {

extern const base::Feature kInterestFeedContentSuggestions_Chromium;

}
#endif  // defined(OS_ANDROID)
#endif  // BRAVE_CHROMIUM_SRC_COMPONENTS_FEED_FEED_FEATURE_LIST_H_
