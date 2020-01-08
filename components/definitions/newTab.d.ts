declare namespace NewTab {
  export interface ApplicationState {
    newTabData: State | undefined
    topSitesData: TopSitesState | undefined
  }

  export interface Image {
    name: string
    source: string
    author: string
    link: string
  }

  export interface Site {
    id: string
    url: string
    title: string
    favicon: string
    letter: string
    pinnedIndex: undefined | number
    bookmarkTreeNode: chrome.bookmarks.BookmarkTreeNode | undefined
  }

  export interface Stats {
    adsBlockedStat: number
    javascriptBlockedStat: number
    httpsUpgradesStat: number
    fingerprintingBlockedStat: number
  }

  export interface Bookmark {
    dateAdded: number
    id: string
    index: number
    parentId: string
    title: string
    url: string
  }

  export interface TopSitesState {
    topSites: chrome.topSites.MostVisitedURL[]
    ignoredTopSites: Site[]
    gridSites: Site[]
    shouldShowSiteRemovalNotification: boolean
  }

  export interface PageState {
    showEmptyPage: boolean
    // TODO: this shouldn't be stored as a list but
    // rather a property of each element on gridSites
    bookmarks: Record<string, Bookmark>
  }

  export interface RewardsState {
    rewardsState: RewardsWidgetState
  }

  export type PersistentState = TopSitesState & PageState & RewardsState

  export interface EphemeralState {
    initialDataLoaded: boolean
    textDirection: string
    isIncognito: boolean
    useAlternativePrivateSearchEngine: boolean
    isTor: boolean
    isQwant: boolean
    backgroundImage?: Image
    gridLayoutSize?: 'small'
    showSiteRemovalNotification?: boolean
    showBackgroundImage: boolean
    showStats: boolean
    showClock: boolean
    showTopSites: boolean
    showRewards: boolean
    stats: Stats
  }

  export interface RewardsWidgetState {
    adsEstimatedEarnings: number
    adsSupported?: boolean
    balance: RewardsBalance
    dismissedNotifications: string[]
    enabledAds: boolean
    enabledMain: boolean
    promotions: Promotion[]
    onlyAnonWallet: boolean
    totalContribution: number
    walletCreated: boolean
    walletCreating: boolean
    walletCreateFailed: boolean
    walletCorrupted: boolean
  }

  export const enum RewardsResult {
    LEDGER_OK = 0,
    LEDGER_ERROR = 1,
    NO_PUBLISHER_STATE = 2,
    NO_LEDGER_STATE = 3,
    INVALID_PUBLISHER_STATE = 4,
    INVALID_LEDGER_STATE = 5,
    CAPTCHA_FAILED = 6,
    NO_PUBLISHER_LIST = 7,
    TOO_MANY_RESULTS = 8,
    NOT_FOUND = 9,
    REGISTRATION_VERIFICATION_FAILED = 10,
    BAD_REGISTRATION_RESPONSE = 11,
    WALLET_CREATED = 12,
    WALLET_CORRUPT = 17
  }

  export interface RewardsBalanceReport {
    ads: number
    contribute: number
    donation: number
    grant: number
    tips: number
  }

  export enum PromotionTypes {
    UGP = 0,
    ADS = 1
  }

  export interface PromotionResponse {
    result: number
    promotions: Promotion[]
  }

  export interface Promotion {
    type: PromotionTypes
    promotionId: string
  }

  export interface RewardsBalance {
    total: number
    rates: Record<string, number>
    wallets: Record<string, number>
  }

  // In-memory state is a superset of PersistentState
  export type State = PersistentState & EphemeralState
}
