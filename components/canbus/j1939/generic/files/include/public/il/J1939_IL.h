
#ifndef __J1939_IL_H__
#define __J1939_IL_H__

#include "J1939_config.h"		// from specific part of J1939 stack

#include "j1939/os/J1939_OS.h"

#include "j1939_section_0.inc"

#ifndef J1939_IL_OPTIM_SIZE_USED
typedef uint16_t    J1939_IL_msg_id_t;      /**< Définition du type des identifiants de message */
typedef uint16_t    J1939_IL_msg_lg_t;      /**< Définition du type de pointeur sur la longueur d'un message */
#else
typedef uint8_t     J1939_IL_msg_id_t;      /**< Définition du type des identifiants de message */
typedef uint8_t     J1939_IL_msg_lg_t;      /**< Définition du type de pointeur sur la longueur d'un message */
#endif

typedef uint8_t     J1939_IL_data_t;        /**< type de donnees */

// layer mode configuration type
typedef enum {
    J1939_IL_OPE    = 0x96,     /**<  Mode operationnel */
    J1939_IL_MAINT  = 0xA5      /**<  Mode specifique maintenance */
} J1939_IL_mode_t;

// COM layer error code
typedef enum {
    J1939_IL_ERR_OK         = 0x69,     /**<  Pas d'erreur */
    J1939_IL_ERR_BADID      = 0x96,     /**<  L'identifiant est erroné */
    J1939_IL_ERR_BADLG      = 0x3C,     /**<  La longueur du message est erronée */
    J1939_IL_ERR_NOTSTARTED = 0xC3,     /**<  La couche n'est pas démarrée */
    J1939_IL_ERR_NOT_IMPL   = 0xA5,     /**<  not implemented */
    J1939_IL_ERR_OTHER      = 0x5A      /**<  Un autre problème non spécifique */
} J1939_IL_status_t;

// COM layer shutdown type
typedef enum {
    J1939_IL_SHUT_DEFERRED  = 0xA5,     /**<  Arrêt différé */
    J1939_IL_SHUT_IMMEDIATE = 0x5A      /**<  Arrêt immédiat */
} J1939_IL_shutdown_t;

// CALLOUT return value
typedef enum {
    J1939_IL_FALSE          = 0x69,     /**<  Retour faut, arrêter le traitement */
    J1939_IL_TRUE           = 0x3C,     /**<  Retour vrai, continuer le traitement */
    J1939_IL_UNCHANGED      = 0xA5      /**<  notification uniquement */
} J1939_IL_cout_return_t;


#ifdef J1939_IL_PERIODIC_TX_USED
#if !defined(J1939_IL_NB_IPDU_PERIODIC_EMS)
#error "In case of J1939_IL_PERIODIC_TX_USED defined, you must define J1939_IL_NB_IPDU_PERIODIC_EMS"
#endif

typedef struct {
    J1939_time_t    period;     /**<  periode d'émission de l'I-PDU */
    J1939_time_t    first;      /**<  offset avant émission du 1er I-PDU */
    J1939_timerId_t id;         /**<  ID du timer dans la partie OS */
} J1939_IL_periodic_t;
#define J1939_IL_PERIODIC_ZERO { .period=0, .first=0, .id=J1939_INVALID_TIMER_ID }
extern const J1939_IL_periodic_t J1939_IL_periodic_zero;
extern const J1939_IL_periodic_t J1939_IL_periodic_tx_g[J1939_IL_NB_IPDU_PERIODIC_EMS];
#endif

typedef void (*J1939_IL_trf_t) (J1939_IL_data_t* ipdu, const J1939_IL_data_t data, J1939_size_t nb_bits, J1939_size_t bit_pos); /**<  pointeur vers une fonction de transfert (msg -> ipdu) optimisé */

typedef struct {
    const J1939_IL_data_t*  init;         /**<  Adresse de la valeur initiale (suite d'octet) */
#ifndef J1939_IL_OPTIMIZATION_TIME_USED
    J1939_size_t            nb_bytes;         /**<  Taille en octet de la valeur initiale */
#endif

    J1939_IL_msg_id_t       ipdu;         /**<  Index de la table TabIPDUEms */
    J1939_size_t            bit_pos;      /**<  Position du 1er bit message dans I-PDU */
    J1939_size_t            nb_bits;      /**<  Taille du message dans l'I-PDU */

#ifndef J1939_IL_OPTIMIZATION_ORDERING_USED
    J1939_IL_trf_t          trf;          /**<  Fonction de transfert du msg vers l'ipdu    */
#endif

#ifdef J1939_IL_TX_TRIGGERED_PROPERTY_USED
    TrfProperty     trfProperty;         /**<  Propriété de transfert */
#endif
} J1939_IL_static_trf_elt_t;
#define J1939_IL_STATIC_TRF_ELT_ZERO { .ipdu=0, .bit_pos=0, .nb_bits=1, .init=0, .trf=0, .nb_bytes=0 }
extern const J1939_IL_static_trf_elt_t J1939_IL_static_trf_elt_zero;
extern const J1939_IL_static_trf_elt_t J1939_IL_static_trf_elt_g[J1939_IL_NB_MSG_TRF_STAT];

/*  Service de gestion de la couche */
/**< Service d'initialisation de la couche interaction */
extern J1939_IL_status_t J1939_IL_start(J1939_IL_mode_t mode);
/**< Service d'arret de la couche interaction */
extern J1939_IL_status_t J1939_IL_stop(J1939_IL_shutdown_t mode);
/**< Service d'arret du monitoring des trames en reception */
extern J1939_IL_status_t J1939_IL_stop_RX_monitoring(void);

#if 0 // not implemented
/**< Service d'initialisation d'un message */
extern J1939_IL_status_t J1939_IL_InitMessage(J1939_IL_msg_id_t id, const J1939_IL_data_t* const dataRef);
/**< Service de démarrage des trames périodiques */
extern J1939_IL_status_t J1939_IL_StartPeriodic(void);
/**< Service d'arret des trames pértiodiques */
extern J1939_IL_status_t J1939_IL_StopPeriodic(void);
/**< Service d'activation ou desactivation de la condition d'un message */
extern J1939_IL_status_t J1939_IL_Change_Tx_Condition(J1939_IL_msg_id_t id, J1939_BOOL cond);
/**< Service de demarrage du monitoring des trames en reception */
extern J1939_IL_status_t J1939_IL_Start_Rx_Monitoring(void);



/*  Service de communication */
/**< Service d'emission d'un message static */
extern J1939_IL_status_t J1939_IL_SendMessage(J1939_IL_msg_id_t id, const J1939_IL_data_t* const dataRef);
/**< Service de reception d'un message static */
extern J1939_IL_status_t J1939_IL_ReceiveMessage(J1939_IL_msg_id_t id, J1939_IL_data_t* const dataRef);
/**< Service d'emission d'un message dynamic */
extern J1939_IL_status_t J1939_IL_SendDynamicMessage(J1939_IL_msg_id_t id, const J1939_IL_data_t* const dataRef, J1939_IL_msg_lg_t* lg);
/**< Service de reception d'un message dynamic */
extern J1939_IL_status_t J1939_IL_ReceiveDynamicMessage(J1939_IL_msg_id_t id, J1939_IL_data_t* const dataRef, J1939_IL_msg_lg_t* lg);
/**< Service d'annulation de l'emission d'un message static */
extern J1939_IL_status_t J1939_IL_CancelMessage(J1939_IL_msg_id_t id);
/**< Service de demarrage du traitement de la gateway */
extern void J1939_IL_StartMessageGateway(void);
/**< Service d'arret du traitement de la gateway */
extern void J1939_IL_StopMessageGateway(void);
/**< Service d'extraction d'un signal uniquement */
extern J1939_IL_status_t J1939_IL_ExtractMessage(J1939_IL_msg_id_t id);



#ifdef RESET_RX_MONITORING_USED
/**<  Service de reinitilisation du monitoring pour un IPDU */
extern J1939_IL_status_t J1939_IL_Reset_Rx_Monitoring(uint8_t monitoredIPDU);
#endif

#endif // not implemented

#include "j1939_section_0.inc"

#endif // __J1939_IL_H__
/*-------------------------------- end of file -------------------------------*/

