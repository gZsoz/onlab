/* Do not modify this file. Changes will be overwritten.                      */
/* Generated automatically by the ASN.1 to Wireshark dissector compiler       */
/* packet-hnbap.c                                                             */
/* asn2wrs.py -q -L -p hnbap -c ./hnbap.cnf -s ./packet-hnbap-template -D . -O ../.. HNBAP-CommonDataTypes.asn HNBAP-Constants.asn HNBAP-Containers.asn HNBAP-IEs.asn HNBAP-PDU-Contents.asn HNBAP-PDU-Descriptions.asn */

/* packet-hnbap-template.c
 * Routines for UMTS Node B Application Part(HNBAP) packet dissection
 * Copyright 2010 Neil Piercy, ip.access Limited <Neil.Piercy@ipaccess.com>
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Ref: 3GPP TS 25.469 version 8.4.0 Release 8
 */

#include "config.h"

#include <epan/packet.h>
#include <epan/sctpppids.h>
#include <epan/asn1.h>
#include <epan/prefs.h>
#include <epan/proto_data.h>
#include <wsutil/array.h>

#include "packet-per.h"
#include "packet-e212.h"

#ifdef _MSC_VER
/* disable: "warning C4146: unary minus operator applied to unsigned type, result still unsigned" */
#pragma warning(disable:4146)
#endif

#define PNAME  "UTRAN Iuh interface HNBAP signalling"
#define PSNAME "HNBAP"
#define PFNAME "hnbap"
/* Dissector will use SCTP PPID 20 or SCTP port. IANA assigned port = 29169*/
#define SCTP_PORT_HNBAP              29169

void proto_register_hnbap(void);

#define maxPrivateIEs                  65535
#define maxProtocolExtensions          65535
#define maxProtocolIEs                 65535
#define maxNrOfErrors                  256
#define maxnoofRABs                    256
#define maxnoofNeighbours              32
#define maxnoofIurhAddresses           3

typedef enum _ProcedureCode_enum {
  id_HNBRegister =   1,
  id_HNBDe_Register =   2,
  id_UERegister =   3,
  id_UEDe_Register =   4,
  id_ErrorIndication =   5,
  id_privateMessage =   6,
  id_CSGMembershipUpdate =   7,
  id_TNLUpdate =   9,
  id_HNBConfigTransfer =  10,
  id_RelocationComplete =  11
} ProcedureCode_enum;

typedef enum _ProtocolIE_ID_enum {
  id_Cause     =   1,
  id_CriticalityDiagnostics =   2,
  id_HNB_Identity =   3,
  id_Context_ID =   4,
  id_UE_Identity =   5,
  id_LAC       =   6,
  id_RAC       =   7,
  id_HNB_Location_Information =   8,
  id_PLMNidentity =   9,
  id_SAC       =  10,
  id_CellIdentity =  11,
  id_Registration_Cause =  12,
  id_UE_Capabilities =  13,
  id_RNC_ID    =  14,
  id_CSG_ID    =  15,
  id_BackoffTimer =  16,
  id_HNB_Internet_Information =  17,
  id_HNB_Cell_Access_Mode =  18,
  id_MuxPortNumber =  19,
  id_Service_Area_For_Broadcast =  20,
  id_CSGMembershipStatus =  21,
  id_RABList   =  22,
  id_HNBConfigInfo =  23,
  id_AccessResult =  25,
  id_Update_cause =  26,
  id_NeighbourInfoList =  27,
  id_NeighbourInfoRequestList =  28,
  id_Iurh_Signalling_TNL_Address =  29,
  id_PSC       =  30,
  id_HNB_Cell_Identifier =  31
} ProtocolIE_ID_enum;

/* Initialize the protocol and registered fields */
static int proto_hnbap;

static int hf_hnbap_BackoffTimer_PDU;             /* BackoffTimer */
static int hf_hnbap_Cause_PDU;                    /* Cause */
static int hf_hnbap_CellIdentity_PDU;             /* CellIdentity */
static int hf_hnbap_Context_ID_PDU;               /* Context_ID */
static int hf_hnbap_CriticalityDiagnostics_PDU;   /* CriticalityDiagnostics */
static int hf_hnbap_CSG_ID_PDU;                   /* CSG_ID */
static int hf_hnbap_CSGMembershipStatus_PDU;      /* CSGMembershipStatus */
static int hf_hnbap_HNB_Cell_Access_Mode_PDU;     /* HNB_Cell_Access_Mode */
static int hf_hnbap_HNB_Location_Information_PDU;  /* HNB_Location_Information */
static int hf_hnbap_HNB_Identity_PDU;             /* HNB_Identity */
static int hf_hnbap_IP_Address_PDU;               /* IP_Address */
static int hf_hnbap_LAC_PDU;                      /* LAC */
static int hf_hnbap_MuxPortNumber_PDU;            /* MuxPortNumber */
static int hf_hnbap_NeighbourInfoList_PDU;        /* NeighbourInfoList */
static int hf_hnbap_NeighbourInfoRequestList_PDU;  /* NeighbourInfoRequestList */
static int hf_hnbap_PLMNidentity_PDU;             /* PLMNidentity */
static int hf_hnbap_PSC_PDU;                      /* PSC */
static int hf_hnbap_RABList_PDU;                  /* RABList */
static int hf_hnbap_RAC_PDU;                      /* RAC */
static int hf_hnbap_Registration_Cause_PDU;       /* Registration_Cause */
static int hf_hnbap_RNC_ID_PDU;                   /* RNC_ID */
static int hf_hnbap_SAC_PDU;                      /* SAC */
static int hf_hnbap_UE_Capabilities_PDU;          /* UE_Capabilities */
static int hf_hnbap_UE_Identity_PDU;              /* UE_Identity */
static int hf_hnbap_Update_cause_PDU;             /* Update_cause */
static int hf_hnbap_HNBRegisterRequest_PDU;       /* HNBRegisterRequest */
static int hf_hnbap_HNBRegisterAccept_PDU;        /* HNBRegisterAccept */
static int hf_hnbap_HNBRegisterReject_PDU;        /* HNBRegisterReject */
static int hf_hnbap_HNBDe_Register_PDU;           /* HNBDe_Register */
static int hf_hnbap_UERegisterRequest_PDU;        /* UERegisterRequest */
static int hf_hnbap_UERegisterAccept_PDU;         /* UERegisterAccept */
static int hf_hnbap_UERegisterReject_PDU;         /* UERegisterReject */
static int hf_hnbap_UEDe_Register_PDU;            /* UEDe_Register */
static int hf_hnbap_CSGMembershipUpdate_PDU;      /* CSGMembershipUpdate */
static int hf_hnbap_TNLUpdateRequest_PDU;         /* TNLUpdateRequest */
static int hf_hnbap_TNLUpdateResponse_PDU;        /* TNLUpdateResponse */
static int hf_hnbap_TNLUpdateFailure_PDU;         /* TNLUpdateFailure */
static int hf_hnbap_HNBConfigTransferRequest_PDU;  /* HNBConfigTransferRequest */
static int hf_hnbap_HNBConfigTransferResponse_PDU;  /* HNBConfigTransferResponse */
static int hf_hnbap_RelocationComplete_PDU;       /* RelocationComplete */
static int hf_hnbap_ErrorIndication_PDU;          /* ErrorIndication */
static int hf_hnbap_PrivateMessage_PDU;           /* PrivateMessage */
static int hf_hnbap_HNBAP_PDU_PDU;                /* HNBAP_PDU */
static int hf_hnbap_local;                        /* INTEGER_0_65535 */
static int hf_hnbap_global;                       /* OBJECT_IDENTIFIER */
static int hf_hnbap_ProtocolIE_Container_item;    /* ProtocolIE_Field */
static int hf_hnbap_protocol_ie_field_id;         /* ProtocolIE_ID */
static int hf_hnbap_criticality;                  /* Criticality */
static int hf_hnbap_ie_field_value;               /* ProtocolIE_Field_value */
static int hf_hnbap_ProtocolExtensionContainer_item;  /* ProtocolExtensionField */
static int hf_hnbap_id;                           /* ProtocolIE_ID */
static int hf_hnbap_extensionValue;               /* T_extensionValue */
static int hf_hnbap_PrivateIE_Container_item;     /* PrivateIE_Field */
static int hf_hnbap_private_ie_field_id;          /* PrivateIE_ID */
static int hf_hnbap_private_value;                /* PrivateIE_Field_value */
static int hf_hnbap_directionOfAltitude;          /* T_directionOfAltitude */
static int hf_hnbap_altitude;                     /* INTEGER_0_32767 */
static int hf_hnbap_radioNetwork;                 /* CauseRadioNetwork */
static int hf_hnbap_transport;                    /* CauseTransport */
static int hf_hnbap_protocol;                     /* CauseProtocol */
static int hf_hnbap_misc;                         /* CauseMisc */
static int hf_hnbap_procedureCode;                /* ProcedureCode */
static int hf_hnbap_triggeringMessage;            /* TriggeringMessage */
static int hf_hnbap_procedureCriticality;         /* Criticality */
static int hf_hnbap_iEsCriticalityDiagnostics;    /* CriticalityDiagnostics_IE_List */
static int hf_hnbap_iE_Extensions;                /* ProtocolExtensionContainer */
static int hf_hnbap_CriticalityDiagnostics_IE_List_item;  /* CriticalityDiagnostics_IE_List_item */
static int hf_hnbap_iECriticality;                /* Criticality */
static int hf_hnbap_iE_ID;                        /* ProtocolIE_ID */
static int hf_hnbap_typeOfError;                  /* TypeOfError */
static int hf_hnbap_pLMNidentity;                 /* PLMNidentity */
static int hf_hnbap_lAC;                          /* LAC */
static int hf_hnbap_cI;                           /* CI */
static int hf_hnbap_geographical_location_geographical_coordinates;  /* GeographicalCoordinates */
static int hf_hnbap_altitudeAndDirection;         /* AltitudeAndDirection */
static int hf_hnbap_latitudeSign;                 /* T_latitudeSign */
static int hf_hnbap_latitude;                     /* INTEGER_0_8388607 */
static int hf_hnbap_longitude;                    /* INTEGER_M8388608_8388607 */
static int hf_hnbap_cellIdentity;                 /* CellIdentity */
static int hf_hnbap_hNB_Identity_as_Cell_Identifier;  /* HNB_Cell_Identifier */
static int hf_hnbap_hnb_RNL_Identity;             /* HNB_RNL_Identity */
static int hf_hnbap_configurationInformation;     /* ConfigurationInformation */
static int hf_hnbap_provided;                     /* HNBConfigurationInformationProvided */
static int hf_hnbap_missing;                      /* HNBConfigurationInformationMissing */
static int hf_hnbap_psc;                          /* PSC */
static int hf_hnbap_cSG_ID;                       /* CSG_ID */
static int hf_hnbap_hNB_Cell_Access_Mode;         /* HNB_Cell_Access_Mode */
static int hf_hnbap_iurh_Signalling_TNL_AddressList;  /* Iurh_Signalling_TNL_AddressList */
static int hf_hnbap_cause;                        /* Cause */
static int hf_hnbap_macroCoverageInfo;            /* MacroCoverageInformation */
static int hf_hnbap_hnb_location_information_geographical_coordinates;  /* GeographicalLocation */
static int hf_hnbap_hNB_Identity_Info;            /* HNB_Identity_Info */
static int hf_hnbap_iMSIDS41;                     /* IMSIDS41 */
static int hf_hnbap_eSN;                          /* ESN */
static int hf_hnbap_ipaddress;                    /* T_ipaddress */
static int hf_hnbap_ipv4info;                     /* Ipv4Address */
static int hf_hnbap_ipv6info;                     /* Ipv6Address */
static int hf_hnbap_Iurh_Signalling_TNL_AddressList_item;  /* IP_Address */
static int hf_hnbap_pLMNID;                       /* PLMNidentity */
static int hf_hnbap_macroCellID;                  /* MacroCellID */
static int hf_hnbap_uTRANCellID;                  /* UTRANCellID */
static int hf_hnbap_gERANCellID;                  /* CGI */
static int hf_hnbap_NeighbourInfoList_item;       /* HNBConfigInfo */
static int hf_hnbap_NeighbourInfoRequestList_item;  /* NeighbourInfoRequestItem */
static int hf_hnbap_pTMSI;                        /* PTMSI */
static int hf_hnbap_rAI;                          /* RAI */
static int hf_hnbap_RABList_item;                 /* RABListItem */
static int hf_hnbap_rAB_ID;                       /* RAB_ID */
static int hf_hnbap_old_transport_Info;           /* TransportInfo */
static int hf_hnbap_new_transport_Info;           /* TransportInfo */
static int hf_hnbap_cn_domain_indicator;          /* CN_DomainIndicator */
static int hf_hnbap_lAI;                          /* LAI */
static int hf_hnbap_rAC;                          /* RAC */
static int hf_hnbap_tMSI;                         /* BIT_STRING_SIZE_32 */
static int hf_hnbap_transportLayerAddress;        /* TransportLayerAddress */
static int hf_hnbap_transportAssociation;         /* T_transportAssociation */
static int hf_hnbap_gtp_TEI;                      /* GTP_TEI */
static int hf_hnbap_bindingID;                    /* BindingID */
static int hf_hnbap_access_stratum_release_indicator;  /* Access_stratum_release_indicator */
static int hf_hnbap_csg_capability;               /* CSG_Capability */
static int hf_hnbap_uTRANcellID;                  /* CellIdentity */
static int hf_hnbap_iMSI;                         /* IMSI */
static int hf_hnbap_tMSILAI;                      /* TMSILAI */
static int hf_hnbap_pTMSIRAI;                     /* PTMSIRAI */
static int hf_hnbap_iMEI;                         /* IMEI */
static int hf_hnbap_iMSIESN;                      /* IMSIESN */
static int hf_hnbap_tMSIDS41;                     /* TMSIDS41 */
static int hf_hnbap_protocolIEs;                  /* ProtocolIE_Container */
static int hf_hnbap_protocolExtensions;           /* ProtocolExtensionContainer */
static int hf_hnbap_privateIEs;                   /* PrivateIE_Container */
static int hf_hnbap_initiatingMessage;            /* InitiatingMessage */
static int hf_hnbap_successfulOutcome;            /* SuccessfulOutcome */
static int hf_hnbap_unsuccessfulOutcome;          /* UnsuccessfulOutcome */
static int hf_hnbap_initiatingMessagevalue;       /* InitiatingMessage_value */
static int hf_hnbap_successfulOutcome_value;      /* SuccessfulOutcome_value */
static int hf_hnbap_unsuccessfulOutcome_value;    /* UnsuccessfulOutcome_value */

/* Initialize the subtree pointers */
static int ett_hnbap;
static int ett_hnbap_imsi;
static int ett_hnbap_PrivateIE_ID;
static int ett_hnbap_ProtocolIE_Container;
static int ett_hnbap_ProtocolIE_Field;
static int ett_hnbap_ProtocolExtensionContainer;
static int ett_hnbap_ProtocolExtensionField;
static int ett_hnbap_PrivateIE_Container;
static int ett_hnbap_PrivateIE_Field;
static int ett_hnbap_AltitudeAndDirection;
static int ett_hnbap_Cause;
static int ett_hnbap_CriticalityDiagnostics;
static int ett_hnbap_CriticalityDiagnostics_IE_List;
static int ett_hnbap_CriticalityDiagnostics_IE_List_item;
static int ett_hnbap_CGI;
static int ett_hnbap_GeographicalLocation;
static int ett_hnbap_GeographicalCoordinates;
static int ett_hnbap_HNB_Cell_Identifier;
static int ett_hnbap_HNB_RNL_Identity;
static int ett_hnbap_HNBConfigInfo;
static int ett_hnbap_ConfigurationInformation;
static int ett_hnbap_HNBConfigurationInformationProvided;
static int ett_hnbap_HNBConfigurationInformationMissing;
static int ett_hnbap_HNB_Location_Information;
static int ett_hnbap_HNB_Identity;
static int ett_hnbap_IMSIESN;
static int ett_hnbap_IP_Address;
static int ett_hnbap_T_ipaddress;
static int ett_hnbap_Iurh_Signalling_TNL_AddressList;
static int ett_hnbap_LAI;
static int ett_hnbap_MacroCoverageInformation;
static int ett_hnbap_MacroCellID;
static int ett_hnbap_NeighbourInfoList;
static int ett_hnbap_NeighbourInfoRequestList;
static int ett_hnbap_NeighbourInfoRequestItem;
static int ett_hnbap_PTMSIRAI;
static int ett_hnbap_RABList;
static int ett_hnbap_RABListItem;
static int ett_hnbap_RAI;
static int ett_hnbap_TMSILAI;
static int ett_hnbap_TransportInfo;
static int ett_hnbap_T_transportAssociation;
static int ett_hnbap_UE_Capabilities;
static int ett_hnbap_UTRANCellID;
static int ett_hnbap_UE_Identity;
static int ett_hnbap_HNBRegisterRequest;
static int ett_hnbap_HNBRegisterAccept;
static int ett_hnbap_HNBRegisterReject;
static int ett_hnbap_HNBDe_Register;
static int ett_hnbap_UERegisterRequest;
static int ett_hnbap_UERegisterAccept;
static int ett_hnbap_UERegisterReject;
static int ett_hnbap_UEDe_Register;
static int ett_hnbap_CSGMembershipUpdate;
static int ett_hnbap_TNLUpdateRequest;
static int ett_hnbap_TNLUpdateResponse;
static int ett_hnbap_TNLUpdateFailure;
static int ett_hnbap_HNBConfigTransferRequest;
static int ett_hnbap_HNBConfigTransferResponse;
static int ett_hnbap_RelocationComplete;
static int ett_hnbap_ErrorIndication;
static int ett_hnbap_PrivateMessage;
static int ett_hnbap_HNBAP_PDU;
static int ett_hnbap_InitiatingMessage;
static int ett_hnbap_SuccessfulOutcome;
static int ett_hnbap_UnsuccessfulOutcome;

struct hnbap_private_data {
  e212_number_type_t number_type;
};

/* Global variables */
static uint32_t ProcedureCode;
static uint32_t ProtocolIE_ID;

/* Dissector tables */
static dissector_table_t hnbap_ies_dissector_table;
static dissector_table_t hnbap_extension_dissector_table;
static dissector_table_t hnbap_proc_imsg_dissector_table;
static dissector_table_t hnbap_proc_sout_dissector_table;
static dissector_table_t hnbap_proc_uout_dissector_table;

static dissector_handle_t hnbap_handle;

static int dissect_ProtocolIEFieldValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *);
static int dissect_ProtocolExtensionFieldExtensionValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *);
static int dissect_InitiatingMessageValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *);
static int dissect_SuccessfulOutcomeValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *);
static int dissect_UnsuccessfulOutcomeValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *);
void proto_reg_handoff_hnbap(void);

static struct hnbap_private_data*
hnbap_get_private_data(packet_info *pinfo)
{
  struct hnbap_private_data *hnbap_data = (struct hnbap_private_data*)p_get_proto_data(pinfo->pool, pinfo, proto_hnbap, 0);
  if (!hnbap_data) {
    hnbap_data = wmem_new0(pinfo->pool, struct hnbap_private_data);
    p_add_proto_data(pinfo->pool, pinfo, proto_hnbap, 0, hnbap_data);
  }
  return hnbap_data;
}


static const value_string hnbap_Criticality_vals[] = {
  {   0, "reject" },
  {   1, "ignore" },
  {   2, "notify" },
  { 0, NULL }
};


static int
dissect_hnbap_Criticality(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, false, 0, NULL);

  return offset;
}



static int
dissect_hnbap_INTEGER_0_65535(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 65535U, NULL, false);

  return offset;
}



static int
dissect_hnbap_OBJECT_IDENTIFIER(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_object_identifier(tvb, offset, actx, tree, hf_index, NULL);

  return offset;
}


static const value_string hnbap_PrivateIE_ID_vals[] = {
  {   0, "local" },
  {   1, "global" },
  { 0, NULL }
};

static const per_choice_t PrivateIE_ID_choice[] = {
  {   0, &hf_hnbap_local         , ASN1_NO_EXTENSIONS     , dissect_hnbap_INTEGER_0_65535 },
  {   1, &hf_hnbap_global        , ASN1_NO_EXTENSIONS     , dissect_hnbap_OBJECT_IDENTIFIER },
  { 0, NULL, 0, NULL }
};

static int
dissect_hnbap_PrivateIE_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_hnbap_PrivateIE_ID, PrivateIE_ID_choice,
                                 NULL);

  return offset;
}


static const value_string hnbap_ProcedureCode_vals[] = {
  { id_HNBRegister, "id-HNBRegister" },
  { id_HNBDe_Register, "id-HNBDe-Register" },
  { id_UERegister, "id-UERegister" },
  { id_UEDe_Register, "id-UEDe-Register" },
  { id_ErrorIndication, "id-ErrorIndication" },
  { id_privateMessage, "id-privateMessage" },
  { id_CSGMembershipUpdate, "id-CSGMembershipUpdate" },
  { id_TNLUpdate, "id-TNLUpdate" },
  { id_HNBConfigTransfer, "id-HNBConfigTransfer" },
  { id_RelocationComplete, "id-RelocationComplete" },
  { 0, NULL }
};


static int
dissect_hnbap_ProcedureCode(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 255U, &ProcedureCode, false);

  if (strcmp(val_to_str_const(ProcedureCode, hnbap_ProcedureCode_vals, "Unknown"), "Unknown") == 0) {
    col_set_str(actx->pinfo->cinfo, COL_INFO,
                      "Unknown Message");
  } /* Known Procedures should be included below and broken out as ELEMENTARY names to avoid confusion */

  return offset;
}


static const value_string hnbap_ProtocolIE_ID_vals[] = {
  { id_Cause, "id-Cause" },
  { id_CriticalityDiagnostics, "id-CriticalityDiagnostics" },
  { id_HNB_Identity, "id-HNB-Identity" },
  { id_Context_ID, "id-Context-ID" },
  { id_UE_Identity, "id-UE-Identity" },
  { id_LAC, "id-LAC" },
  { id_RAC, "id-RAC" },
  { id_HNB_Location_Information, "id-HNB-Location-Information" },
  { id_PLMNidentity, "id-PLMNidentity" },
  { id_SAC, "id-SAC" },
  { id_CellIdentity, "id-CellIdentity" },
  { id_Registration_Cause, "id-Registration-Cause" },
  { id_UE_Capabilities, "id-UE-Capabilities" },
  { id_RNC_ID, "id-RNC-ID" },
  { id_CSG_ID, "id-CSG-ID" },
  { id_BackoffTimer, "id-BackoffTimer" },
  { id_HNB_Internet_Information, "id-HNB-Internet-Information" },
  { id_HNB_Cell_Access_Mode, "id-HNB-Cell-Access-Mode" },
  { id_MuxPortNumber, "id-MuxPortNumber" },
  { id_Service_Area_For_Broadcast, "id-Service-Area-For-Broadcast" },
  { id_CSGMembershipStatus, "id-CSGMembershipStatus" },
  { id_RABList, "id-RABList" },
  { id_HNBConfigInfo, "id-HNBConfigInfo" },
  { id_AccessResult, "id-AccessResult" },
  { id_Update_cause, "id-Update-cause" },
  { id_NeighbourInfoList, "id-NeighbourInfoList" },
  { id_NeighbourInfoRequestList, "id-NeighbourInfoRequestList" },
  { id_Iurh_Signalling_TNL_Address, "id-Iurh-Signalling-TNL-Address" },
  { id_PSC, "id-PSC" },
  { id_HNB_Cell_Identifier, "id-HNB-Cell-Identifier" },
  { 0, NULL }
};


static int
dissect_hnbap_ProtocolIE_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, maxProtocolIEs, &ProtocolIE_ID, false);

  if (tree) {
    proto_item_append_text(proto_item_get_parent_nth(actx->created_item, 2), ": %s",
                           val_to_str(ProtocolIE_ID, VALS(hnbap_ProtocolIE_ID_vals), "unknown (%d)"));
  }
  return offset;
}


static const value_string hnbap_TriggeringMessage_vals[] = {
  {   0, "initiating-message" },
  {   1, "successful-outcome" },
  {   2, "unsuccessful-outcome" },
  { 0, NULL }
};


static int
dissect_hnbap_TriggeringMessage(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, false, 0, NULL);

  return offset;
}



static int
dissect_hnbap_ProtocolIE_Field_value(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_open_type_pdu_new(tvb, offset, actx, tree, hf_index, dissect_ProtocolIEFieldValue);

  return offset;
}


static const per_sequence_t ProtocolIE_Field_sequence[] = {
  { &hf_hnbap_protocol_ie_field_id, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_ProtocolIE_ID },
  { &hf_hnbap_criticality   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_Criticality },
  { &hf_hnbap_ie_field_value, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_ProtocolIE_Field_value },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_ProtocolIE_Field(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_ProtocolIE_Field, ProtocolIE_Field_sequence);

  return offset;
}


static const per_sequence_t ProtocolIE_Container_sequence_of[1] = {
  { &hf_hnbap_ProtocolIE_Container_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_ProtocolIE_Field },
};

static int
dissect_hnbap_ProtocolIE_Container(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_hnbap_ProtocolIE_Container, ProtocolIE_Container_sequence_of,
                                                  0, maxProtocolIEs, false);

  return offset;
}



static int
dissect_hnbap_T_extensionValue(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_open_type_pdu_new(tvb, offset, actx, tree, hf_index, dissect_ProtocolExtensionFieldExtensionValue);

  return offset;
}


static const per_sequence_t ProtocolExtensionField_sequence[] = {
  { &hf_hnbap_id            , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_ProtocolIE_ID },
  { &hf_hnbap_criticality   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_Criticality },
  { &hf_hnbap_extensionValue, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_T_extensionValue },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_ProtocolExtensionField(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_ProtocolExtensionField, ProtocolExtensionField_sequence);

  return offset;
}


static const per_sequence_t ProtocolExtensionContainer_sequence_of[1] = {
  { &hf_hnbap_ProtocolExtensionContainer_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_ProtocolExtensionField },
};

static int
dissect_hnbap_ProtocolExtensionContainer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_hnbap_ProtocolExtensionContainer, ProtocolExtensionContainer_sequence_of,
                                                  1, maxProtocolExtensions, false);

  return offset;
}



static int
dissect_hnbap_PrivateIE_Field_value(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_open_type(tvb, offset, actx, tree, hf_index, NULL);

  return offset;
}


static const per_sequence_t PrivateIE_Field_sequence[] = {
  { &hf_hnbap_private_ie_field_id, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_PrivateIE_ID },
  { &hf_hnbap_criticality   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_Criticality },
  { &hf_hnbap_private_value , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_PrivateIE_Field_value },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_PrivateIE_Field(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_PrivateIE_Field, PrivateIE_Field_sequence);

  return offset;
}


static const per_sequence_t PrivateIE_Container_sequence_of[1] = {
  { &hf_hnbap_PrivateIE_Container_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_PrivateIE_Field },
};

static int
dissect_hnbap_PrivateIE_Container(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_hnbap_PrivateIE_Container, PrivateIE_Container_sequence_of,
                                                  1, maxPrivateIEs, false);

  return offset;
}


static const value_string hnbap_Access_stratum_release_indicator_vals[] = {
  {   0, "r99" },
  {   1, "rel-4" },
  {   2, "rel-5" },
  {   3, "rel-6" },
  {   4, "rel-7" },
  {   5, "rel-8-and-beyond" },
  { 0, NULL }
};


static int
dissect_hnbap_Access_stratum_release_indicator(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     6, NULL, true, 0, NULL);

  return offset;
}



static const value_string hnbap_T_directionOfAltitude_vals[] = {
  {   0, "height" },
  {   1, "depth" },
  { 0, NULL }
};


static int
dissect_hnbap_T_directionOfAltitude(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, false, 0, NULL);

  return offset;
}



static int
dissect_hnbap_INTEGER_0_32767(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 32767U, NULL, false);

  return offset;
}


static const per_sequence_t AltitudeAndDirection_sequence[] = {
  { &hf_hnbap_directionOfAltitude, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_T_directionOfAltitude },
  { &hf_hnbap_altitude      , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_INTEGER_0_32767 },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_AltitudeAndDirection(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_AltitudeAndDirection, AltitudeAndDirection_sequence);

  return offset;
}



static int
dissect_hnbap_BackoffTimer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 3600U, NULL, false);

  return offset;
}



static int
dissect_hnbap_BindingID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       1, 4, true, NULL);

  return offset;
}


static const value_string hnbap_CauseRadioNetwork_vals[] = {
  {   0, "overload" },
  {   1, "unauthorised-Location" },
  {   2, "unauthorised-HNB" },
  {   3, "hNB-parameter-mismatch" },
  {   4, "invalid-UE-identity" },
  {   5, "uE-not-allowed-on-this-HNB" },
  {   6, "uE-unauthorised" },
  {   7, "connection-with-UE-lost" },
  {   8, "ue-RRC-telease" },
  {   9, "hNB-not-registered" },
  {  10, "unspecified" },
  {  11, "normal" },
  {  12, "uE-relocated" },
  {  13, "ue-registered-in-another-HNB" },
  { 0, NULL }
};


static int
dissect_hnbap_CauseRadioNetwork(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     14, NULL, true, 0, NULL);

  return offset;
}


static const value_string hnbap_CauseTransport_vals[] = {
  {   0, "transport-resource-unavailable" },
  {   1, "unspecified" },
  { 0, NULL }
};


static int
dissect_hnbap_CauseTransport(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, true, 0, NULL);

  return offset;
}


static const value_string hnbap_CauseProtocol_vals[] = {
  {   0, "transfer-syntax-error" },
  {   1, "abstract-syntax-error-reject" },
  {   2, "abstract-syntax-error-ignore-and-notify" },
  {   3, "message-not-compatible-with-receiver-state" },
  {   4, "semantic-error" },
  {   5, "unspecified" },
  {   6, "abstract-syntax-error-falsely-constructed-message" },
  { 0, NULL }
};


static int
dissect_hnbap_CauseProtocol(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     7, NULL, true, 0, NULL);

  return offset;
}


static const value_string hnbap_CauseMisc_vals[] = {
  {   0, "processing-overload" },
  {   1, "hardware-failure" },
  {   2, "o-and-m-intervention" },
  {   3, "unspecified" },
  { 0, NULL }
};


static int
dissect_hnbap_CauseMisc(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, true, 0, NULL);

  return offset;
}


static const value_string hnbap_Cause_vals[] = {
  {   0, "radioNetwork" },
  {   1, "transport" },
  {   2, "protocol" },
  {   3, "misc" },
  { 0, NULL }
};

static const per_choice_t Cause_choice[] = {
  {   0, &hf_hnbap_radioNetwork  , ASN1_EXTENSION_ROOT    , dissect_hnbap_CauseRadioNetwork },
  {   1, &hf_hnbap_transport     , ASN1_EXTENSION_ROOT    , dissect_hnbap_CauseTransport },
  {   2, &hf_hnbap_protocol      , ASN1_EXTENSION_ROOT    , dissect_hnbap_CauseProtocol },
  {   3, &hf_hnbap_misc          , ASN1_EXTENSION_ROOT    , dissect_hnbap_CauseMisc },
  { 0, NULL, 0, NULL }
};

static int
dissect_hnbap_Cause(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_hnbap_Cause, Cause_choice,
                                 NULL);

  return offset;
}



static int
dissect_hnbap_CellIdentity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     28, 28, false, NULL, 0, NULL, NULL);

  return offset;
}



static int
dissect_hnbap_Context_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     24, 24, false, NULL, 0, NULL, NULL);

  return offset;
}


static const value_string hnbap_TypeOfError_vals[] = {
  {   0, "not-understood" },
  {   1, "missing" },
  { 0, NULL }
};


static int
dissect_hnbap_TypeOfError(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, true, 0, NULL);

  return offset;
}


static const per_sequence_t CriticalityDiagnostics_IE_List_item_sequence[] = {
  { &hf_hnbap_iECriticality , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_Criticality },
  { &hf_hnbap_iE_ID         , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_ProtocolIE_ID },
  { &hf_hnbap_typeOfError   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_TypeOfError },
  { &hf_hnbap_iE_Extensions , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_CriticalityDiagnostics_IE_List_item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_CriticalityDiagnostics_IE_List_item, CriticalityDiagnostics_IE_List_item_sequence);

  return offset;
}


static const per_sequence_t CriticalityDiagnostics_IE_List_sequence_of[1] = {
  { &hf_hnbap_CriticalityDiagnostics_IE_List_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_CriticalityDiagnostics_IE_List_item },
};

static int
dissect_hnbap_CriticalityDiagnostics_IE_List(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_hnbap_CriticalityDiagnostics_IE_List, CriticalityDiagnostics_IE_List_sequence_of,
                                                  1, maxNrOfErrors, false);

  return offset;
}


static const per_sequence_t CriticalityDiagnostics_sequence[] = {
  { &hf_hnbap_procedureCode , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProcedureCode },
  { &hf_hnbap_triggeringMessage, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_TriggeringMessage },
  { &hf_hnbap_procedureCriticality, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_Criticality },
  { &hf_hnbap_iEsCriticalityDiagnostics, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_CriticalityDiagnostics_IE_List },
  { &hf_hnbap_iE_Extensions , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_CriticalityDiagnostics(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_CriticalityDiagnostics, CriticalityDiagnostics_sequence);

  return offset;
}



static int
dissect_hnbap_CSG_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     27, 27, false, NULL, 0, NULL, NULL);

  return offset;
}


static const value_string hnbap_CSG_Capability_vals[] = {
  {   0, "csg-capable" },
  {   1, "not-csg-capable" },
  { 0, NULL }
};


static int
dissect_hnbap_CSG_Capability(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, true, 0, NULL);

  return offset;
}


static const value_string hnbap_CSGMembershipStatus_vals[] = {
  {   0, "member" },
  {   1, "non-member" },
  { 0, NULL }
};


static int
dissect_hnbap_CSGMembershipStatus(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, true, 0, NULL);

  return offset;
}



static int
dissect_hnbap_PLMNidentity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  tvbuff_t *parameter_tvb;
  struct hnbap_private_data *hnbap_data = hnbap_get_private_data(actx->pinfo);
  e212_number_type_t number_type = hnbap_data->number_type;
  hnbap_data->number_type = E212_NONE;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       3, 3, false, &parameter_tvb);

  if (parameter_tvb) {
    dissect_e212_mcc_mnc(parameter_tvb, actx->pinfo, tree, 0, number_type, false);
  }

  return offset;
}



static int
dissect_hnbap_LAC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, -1,
                                       2, 2, false, &parameter_tvb);

  if (parameter_tvb) {
    actx->created_item = proto_tree_add_item(tree, hf_index, parameter_tvb, 0, 2, ENC_BIG_ENDIAN);
  }


  return offset;
}



static int
dissect_hnbap_CI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       2, 2, false, NULL);

  return offset;
}


static const per_sequence_t CGI_sequence[] = {
  { &hf_hnbap_pLMNidentity  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_PLMNidentity },
  { &hf_hnbap_lAC           , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_LAC },
  { &hf_hnbap_cI            , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_CI },
  { &hf_hnbap_iE_Extensions , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_CGI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  struct hnbap_private_data *hnbap_data = hnbap_get_private_data(actx->pinfo);
  hnbap_data->number_type = E212_CGI;
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_CGI, CGI_sequence);



  return offset;
}


static const value_string hnbap_CN_DomainIndicator_vals[] = {
  {   0, "cs-domain" },
  {   1, "ps-domain" },
  { 0, NULL }
};


static int
dissect_hnbap_CN_DomainIndicator(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, false, 0, NULL);

  return offset;
}



static int
dissect_hnbap_ESN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     32, 32, false, NULL, 0, NULL, NULL);

  return offset;
}


static const value_string hnbap_T_latitudeSign_vals[] = {
  {   0, "north" },
  {   1, "south" },
  { 0, NULL }
};


static int
dissect_hnbap_T_latitudeSign(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, false, 0, NULL);

  return offset;
}



static int
dissect_hnbap_INTEGER_0_8388607(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 8388607U, NULL, false);

  return offset;
}



static int
dissect_hnbap_INTEGER_M8388608_8388607(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            -8388608, 8388607U, NULL, false);

  return offset;
}


static const per_sequence_t GeographicalCoordinates_sequence[] = {
  { &hf_hnbap_latitudeSign  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_T_latitudeSign },
  { &hf_hnbap_latitude      , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_INTEGER_0_8388607 },
  { &hf_hnbap_longitude     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_INTEGER_M8388608_8388607 },
  { &hf_hnbap_iE_Extensions , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_GeographicalCoordinates(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_GeographicalCoordinates, GeographicalCoordinates_sequence);

  return offset;
}


static const per_sequence_t GeographicalLocation_sequence[] = {
  { &hf_hnbap_geographical_location_geographical_coordinates, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_GeographicalCoordinates },
  { &hf_hnbap_altitudeAndDirection, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_AltitudeAndDirection },
  { &hf_hnbap_iE_Extensions , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_GeographicalLocation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_GeographicalLocation, GeographicalLocation_sequence);

  return offset;
}



static int
dissect_hnbap_GTP_TEI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       4, 4, false, NULL);

  return offset;
}


static const value_string hnbap_HNB_Cell_Access_Mode_vals[] = {
  {   0, "closed" },
  {   1, "hybrid" },
  {   2, "open" },
  { 0, NULL }
};


static int
dissect_hnbap_HNB_Cell_Access_Mode(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, true, 0, NULL);

  return offset;
}


static const per_sequence_t HNB_Cell_Identifier_sequence[] = {
  { &hf_hnbap_pLMNidentity  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_PLMNidentity },
  { &hf_hnbap_cellIdentity  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_CellIdentity },
  { &hf_hnbap_iE_Extensions , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_HNB_Cell_Identifier(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_HNB_Cell_Identifier, HNB_Cell_Identifier_sequence);

  return offset;
}


static const value_string hnbap_HNB_RNL_Identity_vals[] = {
  {   0, "hNB-Identity-as-Cell-Identifier" },
  { 0, NULL }
};

static const per_choice_t HNB_RNL_Identity_choice[] = {
  {   0, &hf_hnbap_hNB_Identity_as_Cell_Identifier, ASN1_EXTENSION_ROOT    , dissect_hnbap_HNB_Cell_Identifier },
  { 0, NULL, 0, NULL }
};

static int
dissect_hnbap_HNB_RNL_Identity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_hnbap_HNB_RNL_Identity, HNB_RNL_Identity_choice,
                                 NULL);

  return offset;
}



static int
dissect_hnbap_PSC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     9, 9, false, NULL, 0, NULL, NULL);

  return offset;
}



static int
dissect_hnbap_Ipv4Address(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       4, 4, false, NULL);

  return offset;
}



static int
dissect_hnbap_Ipv6Address(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       16, 16, false, NULL);

  return offset;
}


static const value_string hnbap_T_ipaddress_vals[] = {
  {   0, "ipv4info" },
  {   1, "ipv6info" },
  { 0, NULL }
};

static const per_choice_t T_ipaddress_choice[] = {
  {   0, &hf_hnbap_ipv4info      , ASN1_EXTENSION_ROOT    , dissect_hnbap_Ipv4Address },
  {   1, &hf_hnbap_ipv6info      , ASN1_EXTENSION_ROOT    , dissect_hnbap_Ipv6Address },
  { 0, NULL, 0, NULL }
};

static int
dissect_hnbap_T_ipaddress(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_hnbap_T_ipaddress, T_ipaddress_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t IP_Address_sequence[] = {
  { &hf_hnbap_ipaddress     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_T_ipaddress },
  { &hf_hnbap_iE_Extensions , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_IP_Address(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_IP_Address, IP_Address_sequence);

  return offset;
}


static const per_sequence_t Iurh_Signalling_TNL_AddressList_sequence_of[1] = {
  { &hf_hnbap_Iurh_Signalling_TNL_AddressList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_IP_Address },
};

static int
dissect_hnbap_Iurh_Signalling_TNL_AddressList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_hnbap_Iurh_Signalling_TNL_AddressList, Iurh_Signalling_TNL_AddressList_sequence_of,
                                                  1, maxnoofIurhAddresses, false);

  return offset;
}


static const per_sequence_t HNBConfigurationInformationProvided_sequence[] = {
  { &hf_hnbap_psc           , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_PSC },
  { &hf_hnbap_cSG_ID        , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_CSG_ID },
  { &hf_hnbap_hNB_Cell_Access_Mode, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_HNB_Cell_Access_Mode },
  { &hf_hnbap_iurh_Signalling_TNL_AddressList, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_Iurh_Signalling_TNL_AddressList },
  { &hf_hnbap_iE_Extensions , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_HNBConfigurationInformationProvided(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_HNBConfigurationInformationProvided, HNBConfigurationInformationProvided_sequence);

  return offset;
}


static const per_sequence_t HNBConfigurationInformationMissing_sequence[] = {
  { &hf_hnbap_cause         , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_Cause },
  { &hf_hnbap_iE_Extensions , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_HNBConfigurationInformationMissing(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_HNBConfigurationInformationMissing, HNBConfigurationInformationMissing_sequence);

  return offset;
}


static const value_string hnbap_ConfigurationInformation_vals[] = {
  {   0, "provided" },
  {   1, "missing" },
  { 0, NULL }
};

static const per_choice_t ConfigurationInformation_choice[] = {
  {   0, &hf_hnbap_provided      , ASN1_EXTENSION_ROOT    , dissect_hnbap_HNBConfigurationInformationProvided },
  {   1, &hf_hnbap_missing       , ASN1_EXTENSION_ROOT    , dissect_hnbap_HNBConfigurationInformationMissing },
  { 0, NULL, 0, NULL }
};

static int
dissect_hnbap_ConfigurationInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_hnbap_ConfigurationInformation, ConfigurationInformation_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t HNBConfigInfo_sequence[] = {
  { &hf_hnbap_hnb_RNL_Identity, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_HNB_RNL_Identity },
  { &hf_hnbap_configurationInformation, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_ConfigurationInformation },
  { &hf_hnbap_iE_Extensions , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_HNBConfigInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_HNBConfigInfo, HNBConfigInfo_sequence);

  return offset;
}



static int
dissect_hnbap_RAC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, -1,
                                       1, 1, false, &parameter_tvb);

  if (parameter_tvb) {
    actx->created_item = proto_tree_add_item(tree, hf_index, parameter_tvb, 0, 1, ENC_BIG_ENDIAN);
  }


  return offset;
}


static const per_sequence_t UTRANCellID_sequence[] = {
  { &hf_hnbap_lAC           , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_LAC },
  { &hf_hnbap_rAC           , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_RAC },
  { &hf_hnbap_pLMNidentity  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_PLMNidentity },
  { &hf_hnbap_uTRANcellID   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_CellIdentity },
  { &hf_hnbap_iE_Extensions , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_UTRANCellID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_UTRANCellID, UTRANCellID_sequence);

  return offset;
}


static const value_string hnbap_MacroCellID_vals[] = {
  {   0, "uTRANCellID" },
  {   1, "gERANCellID" },
  { 0, NULL }
};

static const per_choice_t MacroCellID_choice[] = {
  {   0, &hf_hnbap_uTRANCellID   , ASN1_EXTENSION_ROOT    , dissect_hnbap_UTRANCellID },
  {   1, &hf_hnbap_gERANCellID   , ASN1_EXTENSION_ROOT    , dissect_hnbap_CGI },
  { 0, NULL, 0, NULL }
};

static int
dissect_hnbap_MacroCellID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_hnbap_MacroCellID, MacroCellID_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t MacroCoverageInformation_sequence[] = {
  { &hf_hnbap_macroCellID   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_MacroCellID },
  { &hf_hnbap_iE_Extensions , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_MacroCoverageInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_MacroCoverageInformation, MacroCoverageInformation_sequence);

  return offset;
}


static const per_sequence_t HNB_Location_Information_sequence[] = {
  { &hf_hnbap_macroCoverageInfo, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_MacroCoverageInformation },
  { &hf_hnbap_hnb_location_information_geographical_coordinates, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_GeographicalLocation },
  { &hf_hnbap_iE_Extensions , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_HNB_Location_Information(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_HNB_Location_Information, HNB_Location_Information_sequence);

  return offset;
}



static int
dissect_hnbap_HNB_Identity_Info(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       1, 255, false, NULL);

  return offset;
}


static const per_sequence_t HNB_Identity_sequence[] = {
  { &hf_hnbap_hNB_Identity_Info, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_HNB_Identity_Info },
  { &hf_hnbap_iE_Extensions , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_HNB_Identity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_HNB_Identity, HNB_Identity_sequence);

  return offset;
}



static int
dissect_hnbap_IMEI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     60, 60, false, NULL, 0, NULL, NULL);

  return offset;
}



static int
dissect_hnbap_IMSI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  tvbuff_t *parameter_tvb;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       3, 8, false, &parameter_tvb);

  if (parameter_tvb) {
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_hnbap_imsi);
    dissect_e212_imsi(parameter_tvb, actx->pinfo, subtree, 0, tvb_reported_length(parameter_tvb), false);
  }


  return offset;
}



static int
dissect_hnbap_IMSIDS41(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       5, 7, false, NULL);

  return offset;
}


static const per_sequence_t IMSIESN_sequence[] = {
  { &hf_hnbap_iMSIDS41      , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_IMSIDS41 },
  { &hf_hnbap_eSN           , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_ESN },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_IMSIESN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_IMSIESN, IMSIESN_sequence);

  return offset;
}


static const per_sequence_t LAI_sequence[] = {
  { &hf_hnbap_pLMNID        , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_PLMNidentity },
  { &hf_hnbap_lAC           , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_LAC },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_LAI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  struct hnbap_private_data *hnbap_data = hnbap_get_private_data(actx->pinfo);
  /* The RAI is defined in the ASN.1 as the LAI plus the RAC; don't override
   * the MNC/MCC field types in that case.
   */
  if (hnbap_data->number_type != E212_RAI) {
    hnbap_data->number_type = E212_LAI;
  }
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_LAI, LAI_sequence);



  return offset;
}



static int
dissect_hnbap_MuxPortNumber(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1024U, 65535U, NULL, false);

  return offset;
}


static const per_sequence_t NeighbourInfoList_sequence_of[1] = {
  { &hf_hnbap_NeighbourInfoList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_HNBConfigInfo },
};

static int
dissect_hnbap_NeighbourInfoList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_hnbap_NeighbourInfoList, NeighbourInfoList_sequence_of,
                                                  1, maxnoofNeighbours, false);

  return offset;
}


static const per_sequence_t NeighbourInfoRequestItem_sequence[] = {
  { &hf_hnbap_hnb_RNL_Identity, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_HNB_RNL_Identity },
  { &hf_hnbap_iE_Extensions , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_NeighbourInfoRequestItem(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_NeighbourInfoRequestItem, NeighbourInfoRequestItem_sequence);

  return offset;
}


static const per_sequence_t NeighbourInfoRequestList_sequence_of[1] = {
  { &hf_hnbap_NeighbourInfoRequestList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_NeighbourInfoRequestItem },
};

static int
dissect_hnbap_NeighbourInfoRequestList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_hnbap_NeighbourInfoRequestList, NeighbourInfoRequestList_sequence_of,
                                                  1, maxnoofNeighbours, false);

  return offset;
}



static int
dissect_hnbap_PTMSI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     32, 32, false, NULL, 0, NULL, NULL);

  return offset;
}


static const per_sequence_t RAI_sequence[] = {
  { &hf_hnbap_lAI           , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_LAI },
  { &hf_hnbap_rAC           , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_RAC },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_RAI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  struct hnbap_private_data *hnbap_data = hnbap_get_private_data(actx->pinfo);
  hnbap_data->number_type = E212_RAI;
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_RAI, RAI_sequence);



  return offset;
}


static const per_sequence_t PTMSIRAI_sequence[] = {
  { &hf_hnbap_pTMSI         , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_PTMSI },
  { &hf_hnbap_rAI           , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_RAI },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_PTMSIRAI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_PTMSIRAI, PTMSIRAI_sequence);

  return offset;
}



static int
dissect_hnbap_RAB_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     8, 8, false, NULL, 0, NULL, NULL);

  return offset;
}



static int
dissect_hnbap_TransportLayerAddress(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     1, 160, true, NULL, 0, NULL, NULL);

  return offset;
}


static const value_string hnbap_T_transportAssociation_vals[] = {
  {   0, "gtp-TEI" },
  {   1, "bindingID" },
  { 0, NULL }
};

static const per_choice_t T_transportAssociation_choice[] = {
  {   0, &hf_hnbap_gtp_TEI       , ASN1_EXTENSION_ROOT    , dissect_hnbap_GTP_TEI },
  {   1, &hf_hnbap_bindingID     , ASN1_EXTENSION_ROOT    , dissect_hnbap_BindingID },
  { 0, NULL, 0, NULL }
};

static int
dissect_hnbap_T_transportAssociation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_hnbap_T_transportAssociation, T_transportAssociation_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t TransportInfo_sequence[] = {
  { &hf_hnbap_transportLayerAddress, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_TransportLayerAddress },
  { &hf_hnbap_transportAssociation, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_T_transportAssociation },
  { &hf_hnbap_iE_Extensions , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_TransportInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_TransportInfo, TransportInfo_sequence);

  return offset;
}


static const per_sequence_t RABListItem_sequence[] = {
  { &hf_hnbap_rAB_ID        , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_RAB_ID },
  { &hf_hnbap_old_transport_Info, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_TransportInfo },
  { &hf_hnbap_new_transport_Info, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_TransportInfo },
  { &hf_hnbap_cn_domain_indicator, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_CN_DomainIndicator },
  { &hf_hnbap_iE_Extensions , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_RABListItem(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_RABListItem, RABListItem_sequence);

  return offset;
}


static const per_sequence_t RABList_sequence_of[1] = {
  { &hf_hnbap_RABList_item  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_RABListItem },
};

static int
dissect_hnbap_RABList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_hnbap_RABList, RABList_sequence_of,
                                                  1, maxnoofRABs, false);

  return offset;
}


static const value_string hnbap_Registration_Cause_vals[] = {
  {   0, "emergency-call" },
  {   1, "normal" },
  {   2, "ue-relocation" },
  { 0, NULL }
};


static int
dissect_hnbap_Registration_Cause(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, true, 1, NULL);

  return offset;
}



static int
dissect_hnbap_RNC_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 65535U, NULL, false);

  return offset;
}



static int
dissect_hnbap_SAC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, -1,
                                       2, 2, false, &parameter_tvb);

  if (parameter_tvb) {
    actx->created_item = proto_tree_add_item(tree, hf_index, parameter_tvb, 0, 2, ENC_BIG_ENDIAN);
  }


  return offset;
}



static int
dissect_hnbap_BIT_STRING_SIZE_32(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     32, 32, false, NULL, 0, NULL, NULL);

  return offset;
}


static const per_sequence_t TMSILAI_sequence[] = {
  { &hf_hnbap_tMSI          , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_BIT_STRING_SIZE_32 },
  { &hf_hnbap_lAI           , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_LAI },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_TMSILAI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_TMSILAI, TMSILAI_sequence);

  return offset;
}



static int
dissect_hnbap_TMSIDS41(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       2, 17, false, NULL);

  return offset;
}


static const per_sequence_t UE_Capabilities_sequence[] = {
  { &hf_hnbap_access_stratum_release_indicator, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_Access_stratum_release_indicator },
  { &hf_hnbap_csg_capability, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_CSG_Capability },
  { &hf_hnbap_iE_Extensions , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_UE_Capabilities(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_UE_Capabilities, UE_Capabilities_sequence);

  return offset;
}


static const value_string hnbap_UE_Identity_vals[] = {
  {   0, "iMSI" },
  {   1, "tMSILAI" },
  {   2, "pTMSIRAI" },
  {   3, "iMEI" },
  {   4, "eSN" },
  {   5, "iMSIDS41" },
  {   6, "iMSIESN" },
  {   7, "tMSIDS41" },
  { 0, NULL }
};

static const per_choice_t UE_Identity_choice[] = {
  {   0, &hf_hnbap_iMSI          , ASN1_EXTENSION_ROOT    , dissect_hnbap_IMSI },
  {   1, &hf_hnbap_tMSILAI       , ASN1_EXTENSION_ROOT    , dissect_hnbap_TMSILAI },
  {   2, &hf_hnbap_pTMSIRAI      , ASN1_EXTENSION_ROOT    , dissect_hnbap_PTMSIRAI },
  {   3, &hf_hnbap_iMEI          , ASN1_EXTENSION_ROOT    , dissect_hnbap_IMEI },
  {   4, &hf_hnbap_eSN           , ASN1_EXTENSION_ROOT    , dissect_hnbap_ESN },
  {   5, &hf_hnbap_iMSIDS41      , ASN1_EXTENSION_ROOT    , dissect_hnbap_IMSIDS41 },
  {   6, &hf_hnbap_iMSIESN       , ASN1_EXTENSION_ROOT    , dissect_hnbap_IMSIESN },
  {   7, &hf_hnbap_tMSIDS41      , ASN1_EXTENSION_ROOT    , dissect_hnbap_TMSIDS41 },
  { 0, NULL, 0, NULL }
};

static int
dissect_hnbap_UE_Identity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_hnbap_UE_Identity, UE_Identity_choice,
                                 NULL);

  return offset;
}


static const value_string hnbap_Update_cause_vals[] = {
  {   0, "relocation-preparation" },
  { 0, NULL }
};


static int
dissect_hnbap_Update_cause(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, true, 0, NULL);

  return offset;
}


static const per_sequence_t HNBRegisterRequest_sequence[] = {
  { &hf_hnbap_protocolIEs   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_ProtocolIE_Container },
  { &hf_hnbap_protocolExtensions, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_HNBRegisterRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
    col_set_str(actx->pinfo->cinfo, COL_INFO,
               "HNB_REGISTER_REQUEST ");
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_HNBRegisterRequest, HNBRegisterRequest_sequence);



  return offset;
}


static const per_sequence_t HNBRegisterAccept_sequence[] = {
  { &hf_hnbap_protocolIEs   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_ProtocolIE_Container },
  { &hf_hnbap_protocolExtensions, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_HNBRegisterAccept(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
    col_set_str(actx->pinfo->cinfo, COL_INFO,
               "HNB_REGISTER_ACCEPT ");
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_HNBRegisterAccept, HNBRegisterAccept_sequence);



  return offset;
}


static const per_sequence_t HNBRegisterReject_sequence[] = {
  { &hf_hnbap_protocolIEs   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_ProtocolIE_Container },
  { &hf_hnbap_protocolExtensions, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_HNBRegisterReject(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
    col_set_str(actx->pinfo->cinfo, COL_INFO,
               "HNB_REGISTER_REJECT ");
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_HNBRegisterReject, HNBRegisterReject_sequence);



  return offset;
}


static const per_sequence_t HNBDe_Register_sequence[] = {
  { &hf_hnbap_protocolIEs   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_ProtocolIE_Container },
  { &hf_hnbap_protocolExtensions, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_HNBDe_Register(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
    col_set_str(actx->pinfo->cinfo, COL_INFO,
               "HNB_DE-REGISTER ");
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_HNBDe_Register, HNBDe_Register_sequence);



  return offset;
}


static const per_sequence_t UERegisterRequest_sequence[] = {
  { &hf_hnbap_protocolIEs   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_ProtocolIE_Container },
  { &hf_hnbap_protocolExtensions, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_UERegisterRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
    col_set_str(actx->pinfo->cinfo, COL_INFO,
               "UE_REGISTER_REQUEST ");
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_UERegisterRequest, UERegisterRequest_sequence);



  return offset;
}


static const per_sequence_t UERegisterAccept_sequence[] = {
  { &hf_hnbap_protocolIEs   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_ProtocolIE_Container },
  { &hf_hnbap_protocolExtensions, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_UERegisterAccept(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
    col_set_str(actx->pinfo->cinfo, COL_INFO,
               "UE_REGISTER_ACCEPT ");
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_UERegisterAccept, UERegisterAccept_sequence);



  return offset;
}


static const per_sequence_t UERegisterReject_sequence[] = {
  { &hf_hnbap_protocolIEs   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_ProtocolIE_Container },
  { &hf_hnbap_protocolExtensions, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_UERegisterReject(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
    col_set_str(actx->pinfo->cinfo, COL_INFO,
               "UE_REGISTER_REJECT ");
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_UERegisterReject, UERegisterReject_sequence);



  return offset;
}


static const per_sequence_t UEDe_Register_sequence[] = {
  { &hf_hnbap_protocolIEs   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_ProtocolIE_Container },
  { &hf_hnbap_protocolExtensions, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_UEDe_Register(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
    col_set_str(actx->pinfo->cinfo, COL_INFO,
               "UE_DE-REGISTER ");
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_UEDe_Register, UEDe_Register_sequence);



  return offset;
}


static const per_sequence_t CSGMembershipUpdate_sequence[] = {
  { &hf_hnbap_protocolIEs   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_ProtocolIE_Container },
  { &hf_hnbap_protocolExtensions, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_CSGMembershipUpdate(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
    col_set_str(actx->pinfo->cinfo, COL_INFO,
               "CSG_MEMBERSHIP_UPDATE_MESSAGE ");
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_CSGMembershipUpdate, CSGMembershipUpdate_sequence);



  return offset;
}


static const per_sequence_t TNLUpdateRequest_sequence[] = {
  { &hf_hnbap_protocolIEs   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_ProtocolIE_Container },
  { &hf_hnbap_protocolExtensions, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_TNLUpdateRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
    col_set_str(actx->pinfo->cinfo, COL_INFO,
               "TNL_UPDATE_REQUEST_MESSAGE ");
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_TNLUpdateRequest, TNLUpdateRequest_sequence);


  return offset;
}


static const per_sequence_t TNLUpdateResponse_sequence[] = {
  { &hf_hnbap_protocolIEs   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_ProtocolIE_Container },
  { &hf_hnbap_protocolExtensions, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_TNLUpdateResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
    col_set_str(actx->pinfo->cinfo, COL_INFO,
               "TNL_UPDATE_RESPONSE_MESSAGE ");
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_TNLUpdateResponse, TNLUpdateResponse_sequence);


  return offset;
}


static const per_sequence_t TNLUpdateFailure_sequence[] = {
  { &hf_hnbap_protocolIEs   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_ProtocolIE_Container },
  { &hf_hnbap_protocolExtensions, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_TNLUpdateFailure(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
    col_set_str(actx->pinfo->cinfo, COL_INFO,
               "TNL_UPDATE_FAILURE_MESSAGE ");
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_TNLUpdateFailure, TNLUpdateFailure_sequence);


  return offset;
}


static const per_sequence_t HNBConfigTransferRequest_sequence[] = {
  { &hf_hnbap_protocolIEs   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_ProtocolIE_Container },
  { &hf_hnbap_protocolExtensions, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_HNBConfigTransferRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
    col_set_str(actx->pinfo->cinfo, COL_INFO,
               "HNB_CONFIG_TRANSFER_REQUEST_MESSAGE ");
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_HNBConfigTransferRequest, HNBConfigTransferRequest_sequence);


  return offset;
}


static const per_sequence_t HNBConfigTransferResponse_sequence[] = {
  { &hf_hnbap_protocolIEs   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_ProtocolIE_Container },
  { &hf_hnbap_protocolExtensions, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_HNBConfigTransferResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
    col_set_str(actx->pinfo->cinfo, COL_INFO,
               "HNB_CONFIG_TRANSFER_RESPONSE_MESSAGE ");
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_HNBConfigTransferResponse, HNBConfigTransferResponse_sequence);


  return offset;
}


static const per_sequence_t RelocationComplete_sequence[] = {
  { &hf_hnbap_protocolIEs   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_ProtocolIE_Container },
  { &hf_hnbap_protocolExtensions, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_RelocationComplete(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
    col_set_str(actx->pinfo->cinfo, COL_INFO,
               "RELOCATION_COMPLETE_MESSAGE ");
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_RelocationComplete, RelocationComplete_sequence);



  return offset;
}


static const per_sequence_t ErrorIndication_sequence[] = {
  { &hf_hnbap_protocolIEs   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_ProtocolIE_Container },
  { &hf_hnbap_protocolExtensions, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_hnbap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_ErrorIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
    col_set_str(actx->pinfo->cinfo, COL_INFO,
               "ERROR_INDICATION ");
    col_set_fence(actx->pinfo->cinfo, COL_INFO); /* Protect info from CriticalityDiagnostics decodes */
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_ErrorIndication, ErrorIndication_sequence);



  return offset;
}


static const per_sequence_t PrivateMessage_sequence[] = {
  { &hf_hnbap_privateIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_hnbap_PrivateIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_PrivateMessage(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
    col_set_str(actx->pinfo->cinfo, COL_INFO,
               "PRIVATE_MESSAGE ");
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_PrivateMessage, PrivateMessage_sequence);



  return offset;
}



static int
dissect_hnbap_InitiatingMessage_value(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_open_type_pdu_new(tvb, offset, actx, tree, hf_index, dissect_InitiatingMessageValue);

  return offset;
}


static const per_sequence_t InitiatingMessage_sequence[] = {
  { &hf_hnbap_procedureCode , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_ProcedureCode },
  { &hf_hnbap_criticality   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_Criticality },
  { &hf_hnbap_initiatingMessagevalue, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_InitiatingMessage_value },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_InitiatingMessage(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_InitiatingMessage, InitiatingMessage_sequence);

  return offset;
}



static int
dissect_hnbap_SuccessfulOutcome_value(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_open_type_pdu_new(tvb, offset, actx, tree, hf_index, dissect_SuccessfulOutcomeValue);

  return offset;
}


static const per_sequence_t SuccessfulOutcome_sequence[] = {
  { &hf_hnbap_procedureCode , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_ProcedureCode },
  { &hf_hnbap_criticality   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_Criticality },
  { &hf_hnbap_successfulOutcome_value, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_SuccessfulOutcome_value },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_SuccessfulOutcome(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_SuccessfulOutcome, SuccessfulOutcome_sequence);

  return offset;
}



static int
dissect_hnbap_UnsuccessfulOutcome_value(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_open_type_pdu_new(tvb, offset, actx, tree, hf_index, dissect_UnsuccessfulOutcomeValue);

  return offset;
}


static const per_sequence_t UnsuccessfulOutcome_sequence[] = {
  { &hf_hnbap_procedureCode , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_ProcedureCode },
  { &hf_hnbap_criticality   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_Criticality },
  { &hf_hnbap_unsuccessfulOutcome_value, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_hnbap_UnsuccessfulOutcome_value },
  { NULL, 0, 0, NULL }
};

static int
dissect_hnbap_UnsuccessfulOutcome(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_hnbap_UnsuccessfulOutcome, UnsuccessfulOutcome_sequence);

  return offset;
}


static const value_string hnbap_HNBAP_PDU_vals[] = {
  {   0, "initiatingMessage" },
  {   1, "successfulOutcome" },
  {   2, "unsuccessfulOutcome" },
  { 0, NULL }
};

static const per_choice_t HNBAP_PDU_choice[] = {
  {   0, &hf_hnbap_initiatingMessage, ASN1_EXTENSION_ROOT    , dissect_hnbap_InitiatingMessage },
  {   1, &hf_hnbap_successfulOutcome, ASN1_EXTENSION_ROOT    , dissect_hnbap_SuccessfulOutcome },
  {   2, &hf_hnbap_unsuccessfulOutcome, ASN1_EXTENSION_ROOT    , dissect_hnbap_UnsuccessfulOutcome },
  { 0, NULL, 0, NULL }
};

static int
dissect_hnbap_HNBAP_PDU(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_hnbap_HNBAP_PDU, HNBAP_PDU_choice,
                                 NULL);

  return offset;
}

/*--- PDUs ---*/

static int dissect_BackoffTimer_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_BackoffTimer(tvb, offset, &asn1_ctx, tree, hf_hnbap_BackoffTimer_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Cause_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_Cause(tvb, offset, &asn1_ctx, tree, hf_hnbap_Cause_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_CellIdentity_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_CellIdentity(tvb, offset, &asn1_ctx, tree, hf_hnbap_CellIdentity_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Context_ID_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_Context_ID(tvb, offset, &asn1_ctx, tree, hf_hnbap_Context_ID_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_CriticalityDiagnostics_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_CriticalityDiagnostics(tvb, offset, &asn1_ctx, tree, hf_hnbap_CriticalityDiagnostics_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_CSG_ID_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_CSG_ID(tvb, offset, &asn1_ctx, tree, hf_hnbap_CSG_ID_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_CSGMembershipStatus_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_CSGMembershipStatus(tvb, offset, &asn1_ctx, tree, hf_hnbap_CSGMembershipStatus_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_HNB_Cell_Access_Mode_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_HNB_Cell_Access_Mode(tvb, offset, &asn1_ctx, tree, hf_hnbap_HNB_Cell_Access_Mode_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_HNB_Location_Information_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_HNB_Location_Information(tvb, offset, &asn1_ctx, tree, hf_hnbap_HNB_Location_Information_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_HNB_Identity_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_HNB_Identity(tvb, offset, &asn1_ctx, tree, hf_hnbap_HNB_Identity_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_IP_Address_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_IP_Address(tvb, offset, &asn1_ctx, tree, hf_hnbap_IP_Address_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_LAC_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_LAC(tvb, offset, &asn1_ctx, tree, hf_hnbap_LAC_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MuxPortNumber_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_MuxPortNumber(tvb, offset, &asn1_ctx, tree, hf_hnbap_MuxPortNumber_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_NeighbourInfoList_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_NeighbourInfoList(tvb, offset, &asn1_ctx, tree, hf_hnbap_NeighbourInfoList_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_NeighbourInfoRequestList_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_NeighbourInfoRequestList(tvb, offset, &asn1_ctx, tree, hf_hnbap_NeighbourInfoRequestList_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_PLMNidentity_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_PLMNidentity(tvb, offset, &asn1_ctx, tree, hf_hnbap_PLMNidentity_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_PSC_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_PSC(tvb, offset, &asn1_ctx, tree, hf_hnbap_PSC_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_RABList_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_RABList(tvb, offset, &asn1_ctx, tree, hf_hnbap_RABList_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_RAC_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_RAC(tvb, offset, &asn1_ctx, tree, hf_hnbap_RAC_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Registration_Cause_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_Registration_Cause(tvb, offset, &asn1_ctx, tree, hf_hnbap_Registration_Cause_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_RNC_ID_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_RNC_ID(tvb, offset, &asn1_ctx, tree, hf_hnbap_RNC_ID_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_SAC_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_SAC(tvb, offset, &asn1_ctx, tree, hf_hnbap_SAC_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UE_Capabilities_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_UE_Capabilities(tvb, offset, &asn1_ctx, tree, hf_hnbap_UE_Capabilities_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UE_Identity_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_UE_Identity(tvb, offset, &asn1_ctx, tree, hf_hnbap_UE_Identity_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Update_cause_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_Update_cause(tvb, offset, &asn1_ctx, tree, hf_hnbap_Update_cause_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_HNBRegisterRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_HNBRegisterRequest(tvb, offset, &asn1_ctx, tree, hf_hnbap_HNBRegisterRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_HNBRegisterAccept_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_HNBRegisterAccept(tvb, offset, &asn1_ctx, tree, hf_hnbap_HNBRegisterAccept_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_HNBRegisterReject_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_HNBRegisterReject(tvb, offset, &asn1_ctx, tree, hf_hnbap_HNBRegisterReject_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_HNBDe_Register_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_HNBDe_Register(tvb, offset, &asn1_ctx, tree, hf_hnbap_HNBDe_Register_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UERegisterRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_UERegisterRequest(tvb, offset, &asn1_ctx, tree, hf_hnbap_UERegisterRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UERegisterAccept_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_UERegisterAccept(tvb, offset, &asn1_ctx, tree, hf_hnbap_UERegisterAccept_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UERegisterReject_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_UERegisterReject(tvb, offset, &asn1_ctx, tree, hf_hnbap_UERegisterReject_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UEDe_Register_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_UEDe_Register(tvb, offset, &asn1_ctx, tree, hf_hnbap_UEDe_Register_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_CSGMembershipUpdate_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_CSGMembershipUpdate(tvb, offset, &asn1_ctx, tree, hf_hnbap_CSGMembershipUpdate_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_TNLUpdateRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_TNLUpdateRequest(tvb, offset, &asn1_ctx, tree, hf_hnbap_TNLUpdateRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_TNLUpdateResponse_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_TNLUpdateResponse(tvb, offset, &asn1_ctx, tree, hf_hnbap_TNLUpdateResponse_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_TNLUpdateFailure_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_TNLUpdateFailure(tvb, offset, &asn1_ctx, tree, hf_hnbap_TNLUpdateFailure_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_HNBConfigTransferRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_HNBConfigTransferRequest(tvb, offset, &asn1_ctx, tree, hf_hnbap_HNBConfigTransferRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_HNBConfigTransferResponse_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_HNBConfigTransferResponse(tvb, offset, &asn1_ctx, tree, hf_hnbap_HNBConfigTransferResponse_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_RelocationComplete_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_RelocationComplete(tvb, offset, &asn1_ctx, tree, hf_hnbap_RelocationComplete_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ErrorIndication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_ErrorIndication(tvb, offset, &asn1_ctx, tree, hf_hnbap_ErrorIndication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_PrivateMessage_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_PrivateMessage(tvb, offset, &asn1_ctx, tree, hf_hnbap_PrivateMessage_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_HNBAP_PDU_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, true, pinfo);
  offset = dissect_hnbap_HNBAP_PDU(tvb, offset, &asn1_ctx, tree, hf_hnbap_HNBAP_PDU_PDU);
  offset += 7; offset >>= 3;
  return offset;
}


static int dissect_ProtocolIEFieldValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data _U_)
{
  return (dissector_try_uint_with_data(hnbap_ies_dissector_table, ProtocolIE_ID, tvb, pinfo, tree, false, NULL)) ? tvb_captured_length(tvb) : 0;
}

static int dissect_ProtocolExtensionFieldExtensionValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data _U_)
{
  return (dissector_try_uint_with_data(hnbap_extension_dissector_table, ProtocolIE_ID, tvb, pinfo, tree, false, NULL)) ? tvb_captured_length(tvb) : 0;
}
#if 0
static int dissect_InitiatingMessageValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data _U_)
{
  if (!ProcedureCode) return 0;
  return (dissector_try_string_with_data(hnbap_proc_imsg_dissector_table, ProcedureCode, tvb, pinfo, tree, true, NULL)) ? tvb_captured_length(tvb) : 0;
}

static int dissect_SuccessfulOutcomeValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data _U_)
{
  if (!ProcedureCode) return 0;
  return (dissector_try_string_with_data(hnbap_proc_sout_dissector_table, ProcedureCode, tvb, pinfo, tree, true, NULL)) ? tvb_captured_length(tvb) : 0;
}

static int dissect_UnsuccessfulOutcomeValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data _U_)
{
  if (!ProcedureCode) return 0;
  return (dissector_try_string_with_data(hnbap_proc_uout_dissector_table, ProcedureCode, tvb, pinfo, tree, true, NULL)) ? tvb_captured_length(tvb) : 0;
}
#endif

static int dissect_InitiatingMessageValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data _U_)
{
  return (dissector_try_uint_with_data(hnbap_proc_imsg_dissector_table, ProcedureCode, tvb, pinfo, tree, false, NULL)) ? tvb_captured_length(tvb) : 0;
}

static int dissect_SuccessfulOutcomeValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data _U_)
{
  return (dissector_try_uint_with_data(hnbap_proc_sout_dissector_table, ProcedureCode, tvb, pinfo, tree, false, NULL)) ? tvb_captured_length(tvb) : 0;
}

static int dissect_UnsuccessfulOutcomeValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data _U_)
{
  return (dissector_try_uint_with_data(hnbap_proc_uout_dissector_table, ProcedureCode, tvb, pinfo, tree, false, NULL)) ? tvb_captured_length(tvb) : 0;
}

static int
dissect_hnbap(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data)
{
    proto_item  *hnbap_item = NULL;
    proto_tree  *hnbap_tree = NULL;

    /* make entry in the Protocol column on summary display */
    col_set_str(pinfo->cinfo, COL_PROTOCOL, "HNBAP");

    /* create the hnbap protocol tree */
    hnbap_item = proto_tree_add_item(tree, proto_hnbap, tvb, 0, -1, ENC_NA);
    hnbap_tree = proto_item_add_subtree(hnbap_item, ett_hnbap);

    return dissect_HNBAP_PDU_PDU(tvb, pinfo, hnbap_tree, data);
}

/*--- proto_register_hnbap -------------------------------------------*/
void proto_register_hnbap(void) {

  /* List of fields */

  static hf_register_info hf[] = {

    { &hf_hnbap_BackoffTimer_PDU,
      { "BackoffTimer", "hnbap.BackoffTimer",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_Cause_PDU,
      { "Cause", "hnbap.Cause",
        FT_UINT32, BASE_DEC, VALS(hnbap_Cause_vals), 0,
        NULL, HFILL }},
    { &hf_hnbap_CellIdentity_PDU,
      { "CellIdentity", "hnbap.CellIdentity",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_Context_ID_PDU,
      { "Context-ID", "hnbap.Context_ID",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_CriticalityDiagnostics_PDU,
      { "CriticalityDiagnostics", "hnbap.CriticalityDiagnostics_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_CSG_ID_PDU,
      { "CSG-ID", "hnbap.CSG_ID",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_CSGMembershipStatus_PDU,
      { "CSGMembershipStatus", "hnbap.CSGMembershipStatus",
        FT_UINT32, BASE_DEC, VALS(hnbap_CSGMembershipStatus_vals), 0,
        NULL, HFILL }},
    { &hf_hnbap_HNB_Cell_Access_Mode_PDU,
      { "HNB-Cell-Access-Mode", "hnbap.HNB_Cell_Access_Mode",
        FT_UINT32, BASE_DEC, VALS(hnbap_HNB_Cell_Access_Mode_vals), 0,
        NULL, HFILL }},
    { &hf_hnbap_HNB_Location_Information_PDU,
      { "HNB-Location-Information", "hnbap.HNB_Location_Information_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_HNB_Identity_PDU,
      { "HNB-Identity", "hnbap.HNB_Identity_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_IP_Address_PDU,
      { "IP-Address", "hnbap.IP_Address_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_LAC_PDU,
      { "LAC", "hnbap.LAC",
        FT_UINT16, BASE_DEC_HEX, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_MuxPortNumber_PDU,
      { "MuxPortNumber", "hnbap.MuxPortNumber",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_NeighbourInfoList_PDU,
      { "NeighbourInfoList", "hnbap.NeighbourInfoList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_NeighbourInfoRequestList_PDU,
      { "NeighbourInfoRequestList", "hnbap.NeighbourInfoRequestList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_PLMNidentity_PDU,
      { "PLMNidentity", "hnbap.PLMNidentity",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_PSC_PDU,
      { "PSC", "hnbap.PSC",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_RABList_PDU,
      { "RABList", "hnbap.RABList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_RAC_PDU,
      { "RAC", "hnbap.RAC",
        FT_UINT8, BASE_DEC_HEX, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_Registration_Cause_PDU,
      { "Registration-Cause", "hnbap.Registration_Cause",
        FT_UINT32, BASE_DEC, VALS(hnbap_Registration_Cause_vals), 0,
        NULL, HFILL }},
    { &hf_hnbap_RNC_ID_PDU,
      { "RNC-ID", "hnbap.RNC_ID",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_SAC_PDU,
      { "SAC", "hnbap.SAC",
        FT_UINT16, BASE_DEC_HEX, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_UE_Capabilities_PDU,
      { "UE-Capabilities", "hnbap.UE_Capabilities_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_UE_Identity_PDU,
      { "UE-Identity", "hnbap.UE_Identity",
        FT_UINT32, BASE_DEC, VALS(hnbap_UE_Identity_vals), 0,
        NULL, HFILL }},
    { &hf_hnbap_Update_cause_PDU,
      { "Update-cause", "hnbap.Update_cause",
        FT_UINT32, BASE_DEC, VALS(hnbap_Update_cause_vals), 0,
        NULL, HFILL }},
    { &hf_hnbap_HNBRegisterRequest_PDU,
      { "HNBRegisterRequest", "hnbap.HNBRegisterRequest_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_HNBRegisterAccept_PDU,
      { "HNBRegisterAccept", "hnbap.HNBRegisterAccept_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_HNBRegisterReject_PDU,
      { "HNBRegisterReject", "hnbap.HNBRegisterReject_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_HNBDe_Register_PDU,
      { "HNBDe-Register", "hnbap.HNBDe_Register_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_UERegisterRequest_PDU,
      { "UERegisterRequest", "hnbap.UERegisterRequest_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_UERegisterAccept_PDU,
      { "UERegisterAccept", "hnbap.UERegisterAccept_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_UERegisterReject_PDU,
      { "UERegisterReject", "hnbap.UERegisterReject_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_UEDe_Register_PDU,
      { "UEDe-Register", "hnbap.UEDe_Register_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_CSGMembershipUpdate_PDU,
      { "CSGMembershipUpdate", "hnbap.CSGMembershipUpdate_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_TNLUpdateRequest_PDU,
      { "TNLUpdateRequest", "hnbap.TNLUpdateRequest_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_TNLUpdateResponse_PDU,
      { "TNLUpdateResponse", "hnbap.TNLUpdateResponse_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_TNLUpdateFailure_PDU,
      { "TNLUpdateFailure", "hnbap.TNLUpdateFailure_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_HNBConfigTransferRequest_PDU,
      { "HNBConfigTransferRequest", "hnbap.HNBConfigTransferRequest_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_HNBConfigTransferResponse_PDU,
      { "HNBConfigTransferResponse", "hnbap.HNBConfigTransferResponse_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_RelocationComplete_PDU,
      { "RelocationComplete", "hnbap.RelocationComplete_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_ErrorIndication_PDU,
      { "ErrorIndication", "hnbap.ErrorIndication_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_PrivateMessage_PDU,
      { "PrivateMessage", "hnbap.PrivateMessage_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_HNBAP_PDU_PDU,
      { "HNBAP-PDU", "hnbap.HNBAP_PDU",
        FT_UINT32, BASE_DEC, VALS(hnbap_HNBAP_PDU_vals), 0,
        NULL, HFILL }},
    { &hf_hnbap_local,
      { "local", "hnbap.local",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_65535", HFILL }},
    { &hf_hnbap_global,
      { "global", "hnbap.global",
        FT_OID, BASE_NONE, NULL, 0,
        "OBJECT_IDENTIFIER", HFILL }},
    { &hf_hnbap_ProtocolIE_Container_item,
      { "ProtocolIE-Field", "hnbap.ProtocolIE_Field_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_protocol_ie_field_id,
      { "id", "hnbap.protocol_ie_field_id",
        FT_UINT32, BASE_DEC, VALS(hnbap_ProtocolIE_ID_vals), 0,
        "ProtocolIE_ID", HFILL }},
    { &hf_hnbap_criticality,
      { "criticality", "hnbap.criticality",
        FT_UINT32, BASE_DEC, VALS(hnbap_Criticality_vals), 0,
        NULL, HFILL }},
    { &hf_hnbap_ie_field_value,
      { "value", "hnbap.ie_field_value_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "ProtocolIE_Field_value", HFILL }},
    { &hf_hnbap_ProtocolExtensionContainer_item,
      { "ProtocolExtensionField", "hnbap.ProtocolExtensionField_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_id,
      { "id", "hnbap.id",
        FT_UINT32, BASE_DEC, VALS(hnbap_ProtocolIE_ID_vals), 0,
        "ProtocolIE_ID", HFILL }},
    { &hf_hnbap_extensionValue,
      { "extensionValue", "hnbap.extensionValue_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_PrivateIE_Container_item,
      { "PrivateIE-Field", "hnbap.PrivateIE_Field_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_private_ie_field_id,
      { "id", "hnbap.private_ie_field_id",
        FT_UINT32, BASE_DEC, VALS(hnbap_PrivateIE_ID_vals), 0,
        "PrivateIE_ID", HFILL }},
    { &hf_hnbap_private_value,
      { "value", "hnbap.private_value_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "PrivateIE_Field_value", HFILL }},
    { &hf_hnbap_directionOfAltitude,
      { "directionOfAltitude", "hnbap.directionOfAltitude",
        FT_UINT32, BASE_DEC, VALS(hnbap_T_directionOfAltitude_vals), 0,
        NULL, HFILL }},
    { &hf_hnbap_altitude,
      { "altitude", "hnbap.altitude",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_32767", HFILL }},
    { &hf_hnbap_radioNetwork,
      { "radioNetwork", "hnbap.radioNetwork",
        FT_UINT32, BASE_DEC, VALS(hnbap_CauseRadioNetwork_vals), 0,
        "CauseRadioNetwork", HFILL }},
    { &hf_hnbap_transport,
      { "transport", "hnbap.transport",
        FT_UINT32, BASE_DEC, VALS(hnbap_CauseTransport_vals), 0,
        "CauseTransport", HFILL }},
    { &hf_hnbap_protocol,
      { "protocol", "hnbap.protocol",
        FT_UINT32, BASE_DEC, VALS(hnbap_CauseProtocol_vals), 0,
        "CauseProtocol", HFILL }},
    { &hf_hnbap_misc,
      { "misc", "hnbap.misc",
        FT_UINT32, BASE_DEC, VALS(hnbap_CauseMisc_vals), 0,
        "CauseMisc", HFILL }},
    { &hf_hnbap_procedureCode,
      { "procedureCode", "hnbap.procedureCode",
        FT_UINT32, BASE_DEC, VALS(hnbap_ProcedureCode_vals), 0,
        NULL, HFILL }},
    { &hf_hnbap_triggeringMessage,
      { "triggeringMessage", "hnbap.triggeringMessage",
        FT_UINT32, BASE_DEC, VALS(hnbap_TriggeringMessage_vals), 0,
        NULL, HFILL }},
    { &hf_hnbap_procedureCriticality,
      { "procedureCriticality", "hnbap.procedureCriticality",
        FT_UINT32, BASE_DEC, VALS(hnbap_Criticality_vals), 0,
        "Criticality", HFILL }},
    { &hf_hnbap_iEsCriticalityDiagnostics,
      { "iEsCriticalityDiagnostics", "hnbap.iEsCriticalityDiagnostics",
        FT_UINT32, BASE_DEC, NULL, 0,
        "CriticalityDiagnostics_IE_List", HFILL }},
    { &hf_hnbap_iE_Extensions,
      { "iE-Extensions", "hnbap.iE_Extensions",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ProtocolExtensionContainer", HFILL }},
    { &hf_hnbap_CriticalityDiagnostics_IE_List_item,
      { "CriticalityDiagnostics-IE-List item", "hnbap.CriticalityDiagnostics_IE_List_item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_iECriticality,
      { "iECriticality", "hnbap.iECriticality",
        FT_UINT32, BASE_DEC, VALS(hnbap_Criticality_vals), 0,
        "Criticality", HFILL }},
    { &hf_hnbap_iE_ID,
      { "iE-ID", "hnbap.iE_ID",
        FT_UINT32, BASE_DEC, VALS(hnbap_ProtocolIE_ID_vals), 0,
        "ProtocolIE_ID", HFILL }},
    { &hf_hnbap_typeOfError,
      { "typeOfError", "hnbap.typeOfError",
        FT_UINT32, BASE_DEC, VALS(hnbap_TypeOfError_vals), 0,
        NULL, HFILL }},
    { &hf_hnbap_pLMNidentity,
      { "pLMNidentity", "hnbap.pLMNidentity",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_lAC,
      { "lAC", "hnbap.lAC",
        FT_UINT16, BASE_DEC_HEX, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_cI,
      { "cI", "hnbap.cI",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_geographical_location_geographical_coordinates,
      { "geographicalCoordinates", "hnbap.geographical_location_geographical_coordinates_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_altitudeAndDirection,
      { "altitudeAndDirection", "hnbap.altitudeAndDirection_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_latitudeSign,
      { "latitudeSign", "hnbap.latitudeSign",
        FT_UINT32, BASE_DEC, VALS(hnbap_T_latitudeSign_vals), 0,
        NULL, HFILL }},
    { &hf_hnbap_latitude,
      { "latitude", "hnbap.latitude",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_8388607", HFILL }},
    { &hf_hnbap_longitude,
      { "longitude", "hnbap.longitude",
        FT_INT32, BASE_DEC, NULL, 0,
        "INTEGER_M8388608_8388607", HFILL }},
    { &hf_hnbap_cellIdentity,
      { "cellIdentity", "hnbap.cellIdentity",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_hNB_Identity_as_Cell_Identifier,
      { "hNB-Identity-as-Cell-Identifier", "hnbap.hNB_Identity_as_Cell_Identifier_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "HNB_Cell_Identifier", HFILL }},
    { &hf_hnbap_hnb_RNL_Identity,
      { "hnb-RNL-Identity", "hnbap.hnb_RNL_Identity",
        FT_UINT32, BASE_DEC, VALS(hnbap_HNB_RNL_Identity_vals), 0,
        NULL, HFILL }},
    { &hf_hnbap_configurationInformation,
      { "configurationInformation", "hnbap.configurationInformation",
        FT_UINT32, BASE_DEC, VALS(hnbap_ConfigurationInformation_vals), 0,
        NULL, HFILL }},
    { &hf_hnbap_provided,
      { "provided", "hnbap.provided_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "HNBConfigurationInformationProvided", HFILL }},
    { &hf_hnbap_missing,
      { "missing", "hnbap.missing_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "HNBConfigurationInformationMissing", HFILL }},
    { &hf_hnbap_psc,
      { "psc", "hnbap.psc",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_cSG_ID,
      { "cSG-ID", "hnbap.cSG_ID",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_hNB_Cell_Access_Mode,
      { "hNB-Cell-Access-Mode", "hnbap.hNB_Cell_Access_Mode",
        FT_UINT32, BASE_DEC, VALS(hnbap_HNB_Cell_Access_Mode_vals), 0,
        NULL, HFILL }},
    { &hf_hnbap_iurh_Signalling_TNL_AddressList,
      { "iurh-Signalling-TNL-AddressList", "hnbap.iurh_Signalling_TNL_AddressList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_cause,
      { "cause", "hnbap.cause",
        FT_UINT32, BASE_DEC, VALS(hnbap_Cause_vals), 0,
        NULL, HFILL }},
    { &hf_hnbap_macroCoverageInfo,
      { "macroCoverageInfo", "hnbap.macroCoverageInfo_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "MacroCoverageInformation", HFILL }},
    { &hf_hnbap_hnb_location_information_geographical_coordinates,
      { "geographicalCoordinates", "hnbap.hnb_location_information_geographical_coordinates_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "GeographicalLocation", HFILL }},
    { &hf_hnbap_hNB_Identity_Info,
      { "hNB-Identity-Info", "hnbap.hNB_Identity_Info",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_iMSIDS41,
      { "iMSIDS41", "hnbap.iMSIDS41",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_eSN,
      { "eSN", "hnbap.eSN",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_ipaddress,
      { "ipaddress", "hnbap.ipaddress",
        FT_UINT32, BASE_DEC, VALS(hnbap_T_ipaddress_vals), 0,
        NULL, HFILL }},
    { &hf_hnbap_ipv4info,
      { "ipv4info", "hnbap.ipv4info",
        FT_BYTES, BASE_NONE, NULL, 0,
        "Ipv4Address", HFILL }},
    { &hf_hnbap_ipv6info,
      { "ipv6info", "hnbap.ipv6info",
        FT_BYTES, BASE_NONE, NULL, 0,
        "Ipv6Address", HFILL }},
    { &hf_hnbap_Iurh_Signalling_TNL_AddressList_item,
      { "IP-Address", "hnbap.IP_Address_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_pLMNID,
      { "pLMNID", "hnbap.pLMNID",
        FT_BYTES, BASE_NONE, NULL, 0,
        "PLMNidentity", HFILL }},
    { &hf_hnbap_macroCellID,
      { "cellIdentity", "hnbap.macroCellID",
        FT_UINT32, BASE_DEC, VALS(hnbap_MacroCellID_vals), 0,
        "MacroCellID", HFILL }},
    { &hf_hnbap_uTRANCellID,
      { "uTRANCellID", "hnbap.uTRANCellID_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_gERANCellID,
      { "gERANCellID", "hnbap.gERANCellID_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "CGI", HFILL }},
    { &hf_hnbap_NeighbourInfoList_item,
      { "HNBConfigInfo", "hnbap.HNBConfigInfo_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_NeighbourInfoRequestList_item,
      { "NeighbourInfoRequestItem", "hnbap.NeighbourInfoRequestItem_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_pTMSI,
      { "pTMSI", "hnbap.pTMSI",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_rAI,
      { "rAI", "hnbap.rAI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_RABList_item,
      { "RABListItem", "hnbap.RABListItem_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_rAB_ID,
      { "rAB-ID", "hnbap.rAB_ID",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_old_transport_Info,
      { "old-transport-Info", "hnbap.old_transport_Info_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "TransportInfo", HFILL }},
    { &hf_hnbap_new_transport_Info,
      { "new-transport-Info", "hnbap.new_transport_Info_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "TransportInfo", HFILL }},
    { &hf_hnbap_cn_domain_indicator,
      { "cn-domain-indicator", "hnbap.cn_domain_indicator",
        FT_UINT32, BASE_DEC, VALS(hnbap_CN_DomainIndicator_vals), 0,
        "CN_DomainIndicator", HFILL }},
    { &hf_hnbap_lAI,
      { "lAI", "hnbap.lAI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_rAC,
      { "rAC", "hnbap.rAC",
        FT_UINT8, BASE_DEC_HEX, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_tMSI,
      { "tMSI", "hnbap.tMSI",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_32", HFILL }},
    { &hf_hnbap_transportLayerAddress,
      { "transportLayerAddress", "hnbap.transportLayerAddress",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_transportAssociation,
      { "transportAssociation", "hnbap.transportAssociation",
        FT_UINT32, BASE_DEC, VALS(hnbap_T_transportAssociation_vals), 0,
        NULL, HFILL }},
    { &hf_hnbap_gtp_TEI,
      { "gtp-TEI", "hnbap.gtp_TEI",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_bindingID,
      { "bindingID", "hnbap.bindingID",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_access_stratum_release_indicator,
      { "access-stratum-release-indicator", "hnbap.access_stratum_release_indicator",
        FT_UINT32, BASE_DEC, VALS(hnbap_Access_stratum_release_indicator_vals), 0,
        NULL, HFILL }},
    { &hf_hnbap_csg_capability,
      { "csg-capability", "hnbap.csg_capability",
        FT_UINT32, BASE_DEC, VALS(hnbap_CSG_Capability_vals), 0,
        NULL, HFILL }},
    { &hf_hnbap_uTRANcellID,
      { "uTRANcellID", "hnbap.uTRANcellID",
        FT_BYTES, BASE_NONE, NULL, 0,
        "CellIdentity", HFILL }},
    { &hf_hnbap_iMSI,
      { "iMSI", "hnbap.iMSI",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_tMSILAI,
      { "tMSILAI", "hnbap.tMSILAI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_pTMSIRAI,
      { "pTMSIRAI", "hnbap.pTMSIRAI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_iMEI,
      { "iMEI", "hnbap.iMEI",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_iMSIESN,
      { "iMSIESN", "hnbap.iMSIESN_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_tMSIDS41,
      { "tMSIDS41", "hnbap.tMSIDS41",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_protocolIEs,
      { "protocolIEs", "hnbap.protocolIEs",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ProtocolIE_Container", HFILL }},
    { &hf_hnbap_protocolExtensions,
      { "protocolExtensions", "hnbap.protocolExtensions",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ProtocolExtensionContainer", HFILL }},
    { &hf_hnbap_privateIEs,
      { "privateIEs", "hnbap.privateIEs",
        FT_UINT32, BASE_DEC, NULL, 0,
        "PrivateIE_Container", HFILL }},
    { &hf_hnbap_initiatingMessage,
      { "initiatingMessage", "hnbap.initiatingMessage_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_successfulOutcome,
      { "successfulOutcome", "hnbap.successfulOutcome_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_unsuccessfulOutcome,
      { "unsuccessfulOutcome", "hnbap.unsuccessfulOutcome_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_hnbap_initiatingMessagevalue,
      { "value", "hnbap.initiatingMessagevalue_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "InitiatingMessage_value", HFILL }},
    { &hf_hnbap_successfulOutcome_value,
      { "value", "hnbap.successfulOutcome_value_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "SuccessfulOutcome_value", HFILL }},
    { &hf_hnbap_unsuccessfulOutcome_value,
      { "value", "hnbap.unsuccessfulOutcome_value_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "UnsuccessfulOutcome_value", HFILL }},
  };

  /* List of subtrees */
  static int *ett[] = {
          &ett_hnbap,
          &ett_hnbap_imsi,
    &ett_hnbap_PrivateIE_ID,
    &ett_hnbap_ProtocolIE_Container,
    &ett_hnbap_ProtocolIE_Field,
    &ett_hnbap_ProtocolExtensionContainer,
    &ett_hnbap_ProtocolExtensionField,
    &ett_hnbap_PrivateIE_Container,
    &ett_hnbap_PrivateIE_Field,
    &ett_hnbap_AltitudeAndDirection,
    &ett_hnbap_Cause,
    &ett_hnbap_CriticalityDiagnostics,
    &ett_hnbap_CriticalityDiagnostics_IE_List,
    &ett_hnbap_CriticalityDiagnostics_IE_List_item,
    &ett_hnbap_CGI,
    &ett_hnbap_GeographicalLocation,
    &ett_hnbap_GeographicalCoordinates,
    &ett_hnbap_HNB_Cell_Identifier,
    &ett_hnbap_HNB_RNL_Identity,
    &ett_hnbap_HNBConfigInfo,
    &ett_hnbap_ConfigurationInformation,
    &ett_hnbap_HNBConfigurationInformationProvided,
    &ett_hnbap_HNBConfigurationInformationMissing,
    &ett_hnbap_HNB_Location_Information,
    &ett_hnbap_HNB_Identity,
    &ett_hnbap_IMSIESN,
    &ett_hnbap_IP_Address,
    &ett_hnbap_T_ipaddress,
    &ett_hnbap_Iurh_Signalling_TNL_AddressList,
    &ett_hnbap_LAI,
    &ett_hnbap_MacroCoverageInformation,
    &ett_hnbap_MacroCellID,
    &ett_hnbap_NeighbourInfoList,
    &ett_hnbap_NeighbourInfoRequestList,
    &ett_hnbap_NeighbourInfoRequestItem,
    &ett_hnbap_PTMSIRAI,
    &ett_hnbap_RABList,
    &ett_hnbap_RABListItem,
    &ett_hnbap_RAI,
    &ett_hnbap_TMSILAI,
    &ett_hnbap_TransportInfo,
    &ett_hnbap_T_transportAssociation,
    &ett_hnbap_UE_Capabilities,
    &ett_hnbap_UTRANCellID,
    &ett_hnbap_UE_Identity,
    &ett_hnbap_HNBRegisterRequest,
    &ett_hnbap_HNBRegisterAccept,
    &ett_hnbap_HNBRegisterReject,
    &ett_hnbap_HNBDe_Register,
    &ett_hnbap_UERegisterRequest,
    &ett_hnbap_UERegisterAccept,
    &ett_hnbap_UERegisterReject,
    &ett_hnbap_UEDe_Register,
    &ett_hnbap_CSGMembershipUpdate,
    &ett_hnbap_TNLUpdateRequest,
    &ett_hnbap_TNLUpdateResponse,
    &ett_hnbap_TNLUpdateFailure,
    &ett_hnbap_HNBConfigTransferRequest,
    &ett_hnbap_HNBConfigTransferResponse,
    &ett_hnbap_RelocationComplete,
    &ett_hnbap_ErrorIndication,
    &ett_hnbap_PrivateMessage,
    &ett_hnbap_HNBAP_PDU,
    &ett_hnbap_InitiatingMessage,
    &ett_hnbap_SuccessfulOutcome,
    &ett_hnbap_UnsuccessfulOutcome,
  };


  /* Register protocol */
  proto_hnbap = proto_register_protocol(PNAME, PSNAME, PFNAME);
  /* Register fields and subtrees */
  proto_register_field_array(proto_hnbap, hf, array_length(hf));
  proto_register_subtree_array(ett, array_length(ett));

  /* Register dissector */
  hnbap_handle = register_dissector("hnbap", dissect_hnbap, proto_hnbap);

  /* Register dissector tables */
  hnbap_ies_dissector_table = register_dissector_table("hnbap.ies", "HNBAP-PROTOCOL-IES", proto_hnbap, FT_UINT32, BASE_DEC);
  hnbap_extension_dissector_table = register_dissector_table("hnbap.extension", "HNBAP-PROTOCOL-EXTENSION", proto_hnbap, FT_UINT32, BASE_DEC);
  hnbap_proc_imsg_dissector_table = register_dissector_table("hnbap.proc.imsg", "HNBAP-ELEMENTARY-PROCEDURE InitiatingMessage", proto_hnbap, FT_UINT32, BASE_DEC);
  hnbap_proc_sout_dissector_table = register_dissector_table("hnbap.proc.sout", "HNBAP-ELEMENTARY-PROCEDURE SuccessfulOutcome", proto_hnbap, FT_UINT32, BASE_DEC);
  hnbap_proc_uout_dissector_table = register_dissector_table("hnbap.proc.uout", "HNBAP-ELEMENTARY-PROCEDURE UnsuccessfulOutcome", proto_hnbap, FT_UINT32, BASE_DEC);

  /* hnbap_module = prefs_register_protocol(proto_hnbap, NULL); */
}


/*--- proto_reg_handoff_hnbap ---------------------------------------*/
void
proto_reg_handoff_hnbap(void)
{
        dissector_add_uint("sctp.ppi", HNBAP_PAYLOAD_PROTOCOL_ID, hnbap_handle);
        dissector_add_uint_with_preference("sctp.port", SCTP_PORT_HNBAP, hnbap_handle);
  dissector_add_uint("hnbap.ies", id_Cause, create_dissector_handle(dissect_Cause_PDU, proto_hnbap));
  dissector_add_uint("hnbap.ies", id_CriticalityDiagnostics, create_dissector_handle(dissect_CriticalityDiagnostics_PDU, proto_hnbap));
  dissector_add_uint("hnbap.ies", id_HNB_Identity, create_dissector_handle(dissect_HNB_Identity_PDU, proto_hnbap));
  dissector_add_uint("hnbap.ies", id_Context_ID, create_dissector_handle(dissect_Context_ID_PDU, proto_hnbap));
  dissector_add_uint("hnbap.ies", id_UE_Identity, create_dissector_handle(dissect_UE_Identity_PDU, proto_hnbap));
  dissector_add_uint("hnbap.ies", id_LAC, create_dissector_handle(dissect_LAC_PDU, proto_hnbap));
  dissector_add_uint("hnbap.ies", id_RAC, create_dissector_handle(dissect_RAC_PDU, proto_hnbap));
  dissector_add_uint("hnbap.ies", id_HNB_Location_Information, create_dissector_handle(dissect_HNB_Location_Information_PDU, proto_hnbap));
  dissector_add_uint("hnbap.ies", id_PLMNidentity, create_dissector_handle(dissect_PLMNidentity_PDU, proto_hnbap));
  dissector_add_uint("hnbap.ies", id_SAC, create_dissector_handle(dissect_SAC_PDU, proto_hnbap));
  dissector_add_uint("hnbap.ies", id_CellIdentity, create_dissector_handle(dissect_CellIdentity_PDU, proto_hnbap));
  dissector_add_uint("hnbap.ies", id_Registration_Cause, create_dissector_handle(dissect_Registration_Cause_PDU, proto_hnbap));
  dissector_add_uint("hnbap.ies", id_UE_Capabilities, create_dissector_handle(dissect_UE_Capabilities_PDU, proto_hnbap));
  dissector_add_uint("hnbap.ies", id_RNC_ID, create_dissector_handle(dissect_RNC_ID_PDU, proto_hnbap));
  dissector_add_uint("hnbap.ies", id_CSG_ID, create_dissector_handle(dissect_CSG_ID_PDU, proto_hnbap));
  dissector_add_uint("hnbap.ies", id_BackoffTimer, create_dissector_handle(dissect_BackoffTimer_PDU, proto_hnbap));
  dissector_add_uint("hnbap.ies", id_CSGMembershipStatus, create_dissector_handle(dissect_CSGMembershipStatus_PDU, proto_hnbap));
  dissector_add_uint("hnbap.ies", id_RABList, create_dissector_handle(dissect_RABList_PDU, proto_hnbap));
  dissector_add_uint("hnbap.ies", id_Update_cause, create_dissector_handle(dissect_Update_cause_PDU, proto_hnbap));
  dissector_add_uint("hnbap.ies", id_NeighbourInfoList, create_dissector_handle(dissect_NeighbourInfoList_PDU, proto_hnbap));
  dissector_add_uint("hnbap.ies", id_NeighbourInfoRequestList, create_dissector_handle(dissect_NeighbourInfoRequestList_PDU, proto_hnbap));
  dissector_add_uint("hnbap.extension", id_HNB_Internet_Information, create_dissector_handle(dissect_IP_Address_PDU, proto_hnbap));
  dissector_add_uint("hnbap.extension", id_HNB_Cell_Access_Mode, create_dissector_handle(dissect_HNB_Cell_Access_Mode_PDU, proto_hnbap));
  dissector_add_uint("hnbap.extension", id_MuxPortNumber, create_dissector_handle(dissect_MuxPortNumber_PDU, proto_hnbap));
  dissector_add_uint("hnbap.extension", id_CSGMembershipStatus, create_dissector_handle(dissect_CSGMembershipStatus_PDU, proto_hnbap));
  dissector_add_uint("hnbap.extension", id_Iurh_Signalling_TNL_Address, create_dissector_handle(dissect_IP_Address_PDU, proto_hnbap));
  dissector_add_uint("hnbap.extension", id_PSC, create_dissector_handle(dissect_PSC_PDU, proto_hnbap));
  dissector_add_uint("hnbap.proc.imsg", id_HNBRegister, create_dissector_handle(dissect_HNBRegisterRequest_PDU, proto_hnbap));
  dissector_add_uint("hnbap.proc.sout", id_HNBRegister, create_dissector_handle(dissect_HNBRegisterAccept_PDU, proto_hnbap));
  dissector_add_uint("hnbap.proc.uout", id_HNBRegister, create_dissector_handle(dissect_HNBRegisterReject_PDU, proto_hnbap));
  dissector_add_uint("hnbap.proc.imsg", id_UERegister, create_dissector_handle(dissect_UERegisterRequest_PDU, proto_hnbap));
  dissector_add_uint("hnbap.proc.sout", id_UERegister, create_dissector_handle(dissect_UERegisterAccept_PDU, proto_hnbap));
  dissector_add_uint("hnbap.proc.uout", id_UERegister, create_dissector_handle(dissect_UERegisterReject_PDU, proto_hnbap));
  dissector_add_uint("hnbap.proc.imsg", id_TNLUpdate, create_dissector_handle(dissect_TNLUpdateRequest_PDU, proto_hnbap));
  dissector_add_uint("hnbap.proc.sout", id_TNLUpdate, create_dissector_handle(dissect_TNLUpdateResponse_PDU, proto_hnbap));
  dissector_add_uint("hnbap.proc.uout", id_TNLUpdate, create_dissector_handle(dissect_TNLUpdateFailure_PDU, proto_hnbap));
  dissector_add_uint("hnbap.proc.imsg", id_HNBConfigTransfer, create_dissector_handle(dissect_HNBConfigTransferRequest_PDU, proto_hnbap));
  dissector_add_uint("hnbap.proc.sout", id_HNBConfigTransfer, create_dissector_handle(dissect_HNBConfigTransferResponse_PDU, proto_hnbap));
  dissector_add_uint("hnbap.proc.imsg", id_RelocationComplete, create_dissector_handle(dissect_RelocationComplete_PDU, proto_hnbap));
  dissector_add_uint("hnbap.proc.imsg", id_UEDe_Register, create_dissector_handle(dissect_UEDe_Register_PDU, proto_hnbap));
  dissector_add_uint("hnbap.proc.imsg", id_HNBDe_Register, create_dissector_handle(dissect_HNBDe_Register_PDU, proto_hnbap));
  dissector_add_uint("hnbap.proc.imsg", id_ErrorIndication, create_dissector_handle(dissect_ErrorIndication_PDU, proto_hnbap));
  dissector_add_uint("hnbap.proc.imsg", id_CSGMembershipUpdate, create_dissector_handle(dissect_CSGMembershipUpdate_PDU, proto_hnbap));
  dissector_add_uint("hnbap.proc.imsg", id_privateMessage, create_dissector_handle(dissect_PrivateMessage_PDU, proto_hnbap));


}
