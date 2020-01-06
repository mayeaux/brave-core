/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/catalog_campaign_info.h"

namespace ads {

CatalogCampaignInfo::CatalogCampaignInfo() :
    priority(0),
    daily_cap(0) {
}

CatalogCampaignInfo::CatalogCampaignInfo(
    const std::string& campaign_id)
    : campaign_id(campaign_id),
      priority(0),
      daily_cap(0) {
}

CatalogCampaignInfo::CatalogCampaignInfo(
    const CatalogCampaignInfo& info)
    : campaign_id(info.campaign_id),
      priority(info.priority),
      name(info.name),
      start_at(info.start_at),
      end_at(info.end_at),
      daily_cap(info.daily_cap),
      advertiser_id(info.advertiser_id),
      geo_targets(info.geo_targets),
      creative_sets(info.creative_sets) {
}

CatalogCampaignInfo::~CatalogCampaignInfo() = default;

}  // namespace ads
