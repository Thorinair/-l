/********
 * Device Configuration
 *******/

/* Duration of a runtime step in ms. */
#define RUNTIME_STEP 20

/* Interval for lyrics checking in ms (has to be a multiple of RUNTIME_STEP). */
#define LYRICS_INTERVAL 2000

/* Fails until counts as fail. */
#define FAIL_COUNT 4


/********
 * LED Configuration
 *******/

/* Duration of a notification fade in ms (has to be a multiple of RUNTIME_STEP). */
#define LED_NOTIF_FADE 1000

/* Duration to hold the color for in ms (has to be a multiple of RUNTIME_STEP). */
#define LED_NOTIF_HOLD 100

/* Error flicker interval. */
#define LED_ERROR_FLICKER_INT 50

/* Error flicker count. */
#define LED_ERROR_FLICKER_CNT 5

/* How much to boost the LED when pressed. */
#define LED_PRESSED_MULTI 3.0

/* LED colors. */
RGB ledIdleNoLyrics    {80, 10, 0};
RGB ledIdleLyrics      {0, 0, 64};
RGB ledIdleError       {64, 0, 0};

RGB ledNotifWiFiSearch {80, 10, 0};
RGB ledNotifWiFiFail   {96, 0, 0};

RGB ledNotifSuccess    {0, 192, 0};
RGB ledNotifError      {192, 0, 0};
RGB ledNotifNoLyrics   {192, 0, 0};
RGB ledNotifNewTrack   {128, 0, 192};

/* Enable color debugging.
 * The LED will keep glowing in the color set below. 
 * No processing will take place.
 */
#define LED_COLOR_DEBUG false
RGB ledDebug {96, 0, 160};
