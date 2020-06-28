/********
 * LED Configuration
 *******/

/* Duration of a LED animation step in ms. */
#define LED_ANIMATION_INTERVAL 20

/* Duration of a notification fade in ms (has to be a multiple of interval). */
#define LED_NOTIF_FADE 1000

/* Duration to hold the color for in ms (has to be a multiple of interval). */
#define LED_NOTIF_HOLD 100

/* Error flicker interval. */
#define LED_ERROR_FLICKER_INT 50

/* Error flicker count. */
#define LED_ERROR_FLICKER_CNT 5

/* LED colors. */
RGB ledIdle            {0, 0, 64};
RGB ledPressed         {0, 0, 192};

RGB ledNotifWiFiSearch {0, 0, 64};
RGB ledNotifWiFiFail   {64, 0, 0};

RGB ledNotifSuccess    {0, 192, 0};
RGB ledNotifError      {192, 0, 0};
RGB ledNotifNoLyrics   {192, 0, 0};

/* Enable color debugging.
 * The LED will keep glowing in the color set below. 
 * No processing will take place.
 */
#define LED_COLOR_DEBUG false
RGB ledDebug {96, 0, 160};
