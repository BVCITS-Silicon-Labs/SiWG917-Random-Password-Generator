#include "app.h"
#include "sl_si91x_button.h"

#include "sl_si91x_button_init_btn0_config.h"
#include "sl_si91x_button_init_btn1_config.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


/* =========================================================
 * PASSWORD GENERATOR SETTINGS
 * ========================================================= */

#define PASSWORD_LENGTH 12


static const char charset[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789"
    "!@#$%&*";

#define CHARSET_LENGTH (sizeof(charset) - 1)


static char password[PASSWORD_LENGTH + 1];


/* =========================================================
 * REAL-TIME BUTTON EVENT FLAGS
 * ========================================================= */

static volatile bool btn0_pressed = false;
static volatile bool btn1_pressed = false;


/* =========================================================
 * MANUAL BUTTON CONFIGURATION
 *
 * DO NOT use:
 * .port = 0
 * .port = SL_GPIO_PORT_UULP
 *
 * Use the generated button configuration macros.
 * ========================================================= */

/* The generated BTN0 configuration may expand its port macro to UULP_VBAT.
 * This SDK represents the corresponding GPIO port with the value 0. */
#ifndef UULP_VBAT
#define UULP_VBAT 0
#endif

/* BTN1's generated port macro uses HP, which is not defined by this SDK. */
#ifndef HP
#define HP 0
#endif

static const sl_button_t button0 =
{
    .port = SL_BUTTON_BTN0_PORT,
    .pin = SL_BUTTON_BTN0_PIN,
    .button_number = 0,

#ifdef SL_BUTTON_BTN0_PAD
    .pad = SL_BUTTON_BTN0_PAD,
#endif

    .interrupt_config = SL_BUTTON_CONFIG_BTN0_INTR
};

static const sl_button_t button1 = {.port = SL_BUTTON_BTN1_PORT,
                                    .pin = SL_BUTTON_BTN1_PIN,
                                    .button_number = 1,

                                    .interrupt_config =
                                        SL_BUTTON_CONFIG_BTN1_INTR};

/* =========================================================
 * BUTTON INTERRUPT CALLBACK
 *
 * The physical button press reaches here in real time.
 *
 * Do NOT use printf() inside the ISR.
 * ========================================================= */

void sl_si91x_button_isr(uint8_t pin, int8_t state)
{
    /*
     * We only want the PRESS event.
     */
    if (state != BUTTON_PRESSED)
    {
        return;
    }


    /*
     * BTN0
     */
    if (pin == SL_BUTTON_BTN0_PIN)
    {
        btn0_pressed = true;
    }


    /*
     * BTN1
     */
    else if (pin == SL_BUTTON_BTN1_PIN)
    {
        btn1_pressed = true;
    }
}


/* =========================================================
 * MANUAL BUTTON INITIALIZATION
 * ========================================================= */

static void buttons_manual_init(void)
{
    printf("Initializing BTN0...\r\n");

    sl_si91x_button_init(&button0);


    printf("Initializing BTN1...\r\n");

    sl_si91x_button_init(&button1);


    printf("Manual button initialization complete.\r\n");
}


/* =========================================================
 * GENERATE PASSWORD
 * ========================================================= */

static void generate_password(void)
{
    for (uint8_t i = 0; i < PASSWORD_LENGTH; i++)
    {
        password[i] =
            charset[rand() % CHARSET_LENGTH];
    }


    password[PASSWORD_LENGTH] = '\0';


    printf("\r\n");

    printf("========================================\r\n");

    printf("          PASSWORD GENERATOR\r\n");

    printf("========================================\r\n");

    printf("Generated Password : %s\r\n",
           password);

    printf("Password Length    : %d\r\n",
           PASSWORD_LENGTH);

    printf("========================================\r\n");
}


/* =========================================================
 * APPLICATION INITIALIZATION
 * ========================================================= */

void app_init(void)
{
    /*
     * Clear button events.
     */
    btn0_pressed = false;
    btn1_pressed = false;


    /*
     * Initial random seed.
     *
     * This is only a demonstration seed.
     * It is NOT cryptographically secure.
     */
    srand(12345);


    /*
     * Clear password buffer.
     */
    memset(password, 0, sizeof(password));


    /* -----------------------------------------------------
     * STARTUP MESSAGE
     * ----------------------------------------------------- */

    printf("\r\n");

    printf("\r\n");

    printf("========================================\r\n");

    printf("          PASSWORD GENERATOR\r\n");

    printf("========================================\r\n");


    printf("SiWG917 System Started Successfully\r\n");


    /* -----------------------------------------------------
     * BUTTON INFORMATION
     * ----------------------------------------------------- */

    printf("\r\n");

    printf("BUTTON CONTROL\r\n");

    printf("--------------------\r\n");

    printf("BTN0 = Generate Password\r\n");

    printf("BTN1 = Generate New Password\r\n");


    printf("\r\n");

    printf("Password Length : %d\r\n",
           PASSWORD_LENGTH);


    /* -----------------------------------------------------
     * MANUAL BUTTON INITIALIZATION
     * ----------------------------------------------------- */

    printf("\r\n");

    buttons_manual_init();


    /* -----------------------------------------------------
     * READY
     * ----------------------------------------------------- */

    printf("\r\n");

    printf("READY\r\n");

    printf("Press BTN0 or BTN1 to generate a password.\r\n");


    printf("========================================\r\n");
}


/* =========================================================
 * MAIN APPLICATION PROCESS
 * ========================================================= */

void app_process_action(void)
{
    /*
     * =====================================================
     * BTN0 EVENT
     * =====================================================
     */

    if (btn0_pressed)
    {
        /*
         * Clear the event immediately.
         */
        btn0_pressed = false;


        printf("\r\n");

        printf("BTN0 PRESSED\r\n");

        printf("Generating Password...\r\n");


        /*
         * Generate password.
         */
        generate_password();
    }


    /*
     * =====================================================
     * BTN1 EVENT
     * =====================================================
     */

    if (btn1_pressed)
    {
        /*
         * Clear the event immediately.
         */
        btn1_pressed = false;


        printf("\r\n");

        printf("BTN1 PRESSED\r\n");

        printf("Generating New Password...\r\n");


        /*
         * Generate another password.
         */
        generate_password();
    }
}