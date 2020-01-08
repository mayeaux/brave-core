/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

export const isHttpOrHttps = (url?: string) => {
  if (!url) {
    return false
  }
  return /^https?:/i.test(url)
}

/**
 * Obtains a letter / char that represents the current site
 * @param site - The site requested from the top site's list
 */
export const getCharForSite = (site: Partial<NewTab.Site>): string => {
  let name
  if (!site.title) {
    try {
      name = new window.URL(site.url || '').hostname
    } catch (e) {
      console.warn('getCharForSite', { url: site.url || '' })
    }
  }
  name = site.title || name || '?'
  return name.charAt(0).toUpperCase()
}

export const generateTopSiteId = (currentIndex: number): string => {
  return `topsite-${currentIndex}-${Date.now()}`
}

export const generateTopSiteFavicon = (url: string): string => {
  return `chrome://favicon/size/64@1x/${url}`
}

export const isTopSitePinned = (site: NewTab.Site): boolean => {
  return site.pinnedIndex !== undefined
}

export const isTopSiteBookmarked = (
  bookmarkTreeNode: chrome.bookmarks.BookmarkTreeNode | undefined
): boolean => {
  return bookmarkTreeNode !== undefined
}
