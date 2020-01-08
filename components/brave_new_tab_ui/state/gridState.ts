/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

// Utils
import {
  getCharForSite,
  generateTopSiteId,
  generateTopSiteFavicon
} from '../helpers/newTabUtils'
import { gridSitesSize } from '../constants/new_tab_interface'

export const getGridSites = (
  sites: chrome.topSites.MostVisitedURL[]
): NewTab.Site[] => {
  const defaultChromeWebStoreUrl: string = 'https://chrome.google.com/webstore'
  const filteredGridSites: chrome.topSites.MostVisitedURL[] = sites
    .filter(site => {
      // see https://github.com/brave/brave-browser/issues/5376
      return !site.url.startsWith(defaultChromeWebStoreUrl)
    })

  let formattedGridSites: NewTab.Site[] = []
  for (const [index, site] of filteredGridSites.entries()) {
    formattedGridSites = [ ...formattedGridSites, {
      id:  generateTopSiteId(index),
      url: site.url,
      title: site.title,
      letter:  getCharForSite(site),
      favicon:  generateTopSiteFavicon(site.url),
      pinnedIndex: undefined,
      bookmarkTreeNode:  undefined
    }]
  }
  // grid is current restricted to 6 tiles
  return formattedGridSites.slice(0, gridSitesSize)
}
