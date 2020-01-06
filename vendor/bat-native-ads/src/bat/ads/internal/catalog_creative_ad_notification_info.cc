/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/catalog_creative_ad_notification_info.h"

namespace ads {

CatalogCreativeAdNotificationInfo::CatalogCreativeAdNotificationInfo()
    = default;

CatalogCreativeAdNotificationInfo::CatalogCreativeAdNotificationInfo(
    const CatalogCreativeAdNotificationInfo& info)
    : creative_instance_id(info.creative_instance_id),
      type(info.type),
      payload(info.payload) {
}

CatalogCreativeAdNotificationInfo::~CatalogCreativeAdNotificationInfo()
    = default;

}  // namespace ads
