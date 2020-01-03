/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_NTP_SPONSORED_IMAGES_NTP_SPONSORED_IMAGES_SERVICE_H_
#define BRAVE_COMPONENTS_NTP_SPONSORED_IMAGES_NTP_SPONSORED_IMAGES_SERVICE_H_

#include <memory>
#include <string>

#include "base/component_export.h"
#include "base/files/file_path.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/optional.h"
#include "brave/components/brave_component_updater/browser/brave_component.h"
#include "components/component_updater/component_updater_service.h"

struct NTPSponsoredImagesData;

class COMPONENT_EXPORT(BRAVE_COMPONENTS_NTP_SPONSORED_IMAGES)
NTPSponsoredImagesService
    : public brave_component_updater::BraveComponent,
      public component_updater::ServiceObserver  {
 public:
  class Observer {
   public:
    // Called whenever ntp sponsored images component is updated.
    virtual void OnUpdated(const NTPSponsoredImagesData& data) = 0;
   protected:
    virtual ~Observer() {}
  };

  NTPSponsoredImagesService(BraveComponent::Delegate* delegate,
                            component_updater::ComponentUpdateService* cus,
                            const std::string& locale);
  ~NTPSponsoredImagesService() override;

  NTPSponsoredImagesService(const NTPSponsoredImagesService&) = delete;
  NTPSponsoredImagesService operator=(
      const NTPSponsoredImagesService&) = delete;

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  base::Optional<NTPSponsoredImagesData> GetLatestSponsoredImagesData() const;

 private:
  // BraveComponent overrides:
  void OnComponentReady(const std::string& component_id,
                        const base::FilePath& installed_dir,
                        const std::string& manifest) override;

  // ServiceObserver overrides:
  void OnEvent(Events event, const std::string& id) override;

  void ReadPhotoJsonFileAndNotify();
  void OnGetPhotoJsonData(const std::string& photo_json);
  void ParseAndCachePhotoJsonData(const std::string& photo_json);
  void NotifyObservers();

  base::FilePath photo_json_file_path_;
  component_updater::ComponentUpdateService* cus_ = nullptr;
  base::ObserverList<Observer>::Unchecked observer_list_;
  std::unique_ptr<NTPSponsoredImagesData> ntp_sponsored_images_data_;
  base::WeakPtrFactory<NTPSponsoredImagesService> weak_factory_;
};

#endif  // BRAVE_COMPONENTS_NTP_SPONSORED_IMAGES_NTP_SPONSORED_IMAGES_SERVICE_H_
