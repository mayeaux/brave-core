/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_ADS_INTERNAL_CATALOG_CREATIVE_PUBLISHER_AD_INFO_H_
#define BAT_ADS_INTERNAL_CATALOG_CREATIVE_PUBLISHER_AD_INFO_H_

#include <string>
#include <vector>

#include "bat/ads/internal/catalog_type_info.h"
#include "bat/ads/internal/catalog_publisher_ad_payload_info.h"
#include "bat/ads/internal/catalog_publisher_ad_site_info.h"

namespace ads {

struct CatalogCreativePublisherAdInfo {
  CatalogCreativePublisherAdInfo();
  CatalogCreativePublisherAdInfo(
      const CatalogCreativePublisherAdInfo& info);
  ~CatalogCreativePublisherAdInfo();

  std::string creative_instance_id;
  TypeInfo type;
  CatalogPublisherAdPayloadInfo payload;
  std::vector<CatalogPublisherAdSiteInfo> sites;
};

}  // namespace ads

#endif  // BAT_ADS_INTERNAL_CATALOG_CREATIVE_PUBLISHER_AD_INFO_H_
