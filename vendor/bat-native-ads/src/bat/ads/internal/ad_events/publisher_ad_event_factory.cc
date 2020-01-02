/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/ad_events/publisher_ad_event_factory.h"
#include "bat/ads/internal/ad_events/publisher_ad_event_viewed.h"
#include "bat/ads/internal/ad_events/publisher_ad_event_clicked.h"
#include "base/logging.h"

namespace ads {

std::unique_ptr<AdEvent<PublisherAdInfo>> PublisherAdEventFactory::Build(
    AdsImpl* ads,
    const AdEventType event_type) {
  DCHECK(ads);

  switch (event_type) {
    case AdEventType::kViewed: {
      return std::make_unique<PublisherAdEventViewed>(ads);
    }

    case AdEventType::kClicked: {
      return std::make_unique<PublisherAdEventClicked>(ads);
    }

    case AdEventType::kDismissed: {
      NOTREACHED();
      return nullptr;
    }

    case AdEventType::kTimedOut: {
      NOTREACHED();
      return nullptr;
    }
  }
}

}  // namespace ads
