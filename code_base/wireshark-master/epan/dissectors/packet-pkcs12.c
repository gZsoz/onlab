/* Do not modify this file. Changes will be overwritten.                      */
/* Generated automatically by the ASN.1 to Wireshark dissector compiler       */
/* packet-pkcs12.c                                                            */
/* asn2wrs.py -b -q -L -p pkcs12 -c ./pkcs12.cnf -s ./packet-pkcs12-template -D . -O ../.. pkcs12.asn PKCS5v2-1.asn Module-scrypt-0.asn */

/* packet-pkcs12.c
 * Routines for PKCS#12: Personal Information Exchange packet dissection
 * Graeme Lunt 2006
 *
 * See "PKCS #12 v1.1: Personal Information Exchange Syntax":
 *
 *    http://www.emc.com/emc-plus/rsa-labs/pkcs/files/h11301-wp-pkcs-12v1-1-personal-information-exchange-syntax.pdf
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "config.h"

#include <epan/packet.h>
#include <epan/expert.h>
#include <epan/oids.h>
#include <epan/asn1.h>
#include <epan/prefs.h>
#include <wsutil/array.h>

#include "packet-akp.h"
#include "packet-ber.h"
#include "packet-pkcs12.h"
#include "packet-x509af.h"
#include "packet-x509if.h"
#include "packet-cms.h"

#include <wsutil/wsgcrypt.h>

#define PNAME  "PKCS#12: Personal Information Exchange"
#define PSNAME "PKCS12"
#define PFNAME "pkcs12"

#define PKCS12_PBE_ARCFOUR_SHA1_OID     "1.2.840.113549.1.12.1.1"
#define PKCS12_PBE_3DES_SHA1_OID	"1.2.840.113549.1.12.1.3"
#define PKCS12_PBE_RC2_40_SHA1_OID	"1.2.840.113549.1.12.1.6"

void proto_register_pkcs12(void);
void proto_reg_handoff_pkcs12(void);

/* Initialize the protocol and registered fields */
static int proto_pkcs12;

static int hf_pkcs12_X509Certificate_PDU;
static int hf_pkcs12_AuthenticatedSafe_PDU;  /* AuthenticatedSafe */
static int ett_decrypted_pbe;

static expert_field ei_pkcs12_octet_string_expected;


static const char *object_identifier_id;
static int iteration_count;
static tvbuff_t *salt;
static const char *password;
static bool try_null_password;

static int dissect_AuthenticatedSafe_OCTETSTRING_PDU(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void* data);
static int dissect_SafeContents_OCTETSTRING_PDU(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void* data);

static int hf_pkcs12_PFX_PDU;                     /* PFX */
static int hf_pkcs12_SafeContents_PDU;            /* SafeContents */
static int hf_pkcs12_KeyBag_PDU;                  /* KeyBag */
static int hf_pkcs12_PKCS8ShroudedKeyBag_PDU;     /* PKCS8ShroudedKeyBag */
static int hf_pkcs12_CertBag_PDU;                 /* CertBag */
static int hf_pkcs12_CRLBag_PDU;                  /* CRLBag */
static int hf_pkcs12_SecretBag_PDU;               /* SecretBag */
static int hf_pkcs12_Pkcs_12PbeParams_PDU;        /* Pkcs_12PbeParams */
static int hf_pkcs12_PBKDF2_params_PDU;           /* PBKDF2_params */
static int hf_pkcs12_PBEParameter_PDU;            /* PBEParameter */
static int hf_pkcs12_PBES2_params_PDU;            /* PBES2_params */
static int hf_pkcs12_PBMAC1_params_PDU;           /* PBMAC1_params */
static int hf_pkcs12_Scrypt_params_PDU;           /* Scrypt_params */
static int hf_pkcs12_version;                     /* T_version */
static int hf_pkcs12_authSafe;                    /* ContentInfo */
static int hf_pkcs12_macData;                     /* MacData */
static int hf_pkcs12_mac;                         /* DigestInfo */
static int hf_pkcs12_macSalt;                     /* OCTET_STRING */
static int hf_pkcs12_iterations;                  /* INTEGER */
static int hf_pkcs12_AuthenticatedSafe_item;      /* ContentInfo */
static int hf_pkcs12_SafeContents_item;           /* SafeBag */
static int hf_pkcs12_bagId;                       /* T_bagId */
static int hf_pkcs12_bagValue;                    /* T_bagValue */
static int hf_pkcs12_bagAttributes;               /* SET_OF_PKCS12Attribute */
static int hf_pkcs12_bagAttributes_item;          /* PKCS12Attribute */
static int hf_pkcs12_certId;                      /* T_certId */
static int hf_pkcs12_certValue;                   /* T_certValue */
static int hf_pkcs12_crlId;                       /* T_crlId */
static int hf_pkcs12_crlValue;                    /* T_crlValue */
static int hf_pkcs12_secretTypeId;                /* T_secretTypeId */
static int hf_pkcs12_secretValue;                 /* T_secretValue */
static int hf_pkcs12_attrId;                      /* T_attrId */
static int hf_pkcs12_attrValues;                  /* T_attrValues */
static int hf_pkcs12_attrValues_item;             /* T_attrValues_item */
static int hf_pkcs12_salt;                        /* OCTET_STRING */
static int hf_pkcs12_saltChoice;                  /* T_saltChoice */
static int hf_pkcs12_specified;                   /* OCTET_STRING */
static int hf_pkcs12_otherSource;                 /* AlgorithmIdentifier */
static int hf_pkcs12_iterationCount;              /* INTEGER */
static int hf_pkcs12_keyLength;                   /* INTEGER_1_MAX */
static int hf_pkcs12_prf;                         /* AlgorithmIdentifier */
static int hf_pkcs12_keyDerivationFunc;           /* AlgorithmIdentifier */
static int hf_pkcs12_encryptionScheme;            /* AlgorithmIdentifier */
static int hf_pkcs12_messageAuthScheme;           /* AlgorithmIdentifier */
static int hf_pkcs12_costParameter;               /* INTEGER_1_MAX */
static int hf_pkcs12_blockSize;                   /* INTEGER_1_MAX */
static int hf_pkcs12_parallelizationParameter;    /* INTEGER_1_MAX */

/* Initialize the subtree pointers */
static int ett_pkcs12_PFX;
static int ett_pkcs12_MacData;
static int ett_pkcs12_AuthenticatedSafe;
static int ett_pkcs12_SafeContents;
static int ett_pkcs12_SafeBag;
static int ett_pkcs12_SET_OF_PKCS12Attribute;
static int ett_pkcs12_CertBag;
static int ett_pkcs12_CRLBag;
static int ett_pkcs12_SecretBag;
static int ett_pkcs12_PKCS12Attribute;
static int ett_pkcs12_T_attrValues;
static int ett_pkcs12_Pkcs_12PbeParams;
static int ett_pkcs12_PBKDF2_params;
static int ett_pkcs12_T_saltChoice;
static int ett_pkcs12_PBEParameter;
static int ett_pkcs12_PBES2_params;
static int ett_pkcs12_PBMAC1_params;
static int ett_pkcs12_Scrypt_params;

static void append_oid(wmem_allocator_t *pool, proto_tree *tree, const char *oid)
{
  	const char *name = NULL;

	name = oid_resolved_from_string(pool, oid);
	proto_item_append_text(tree, " (%s)", name ? name : oid);
}

static int
generate_key_or_iv(packet_info *pinfo, unsigned int id, tvbuff_t *salt_tvb, unsigned int iter,
		       const char *pw, unsigned int req_keylen, char * keybuf)
{
  int rc;
  unsigned int i, j;
  gcry_md_hd_t md;
  gcry_mpi_t num_b1 = NULL;
  size_t pwlen;
  char hash[20], buf_b[64], buf_i[128], *p;
  char *salt_p;
  int salt_size;
  size_t cur_keylen;
  size_t n;
  gcry_error_t	err;

  cur_keylen = 0;

  salt_size = tvb_captured_length(salt_tvb);
  salt_p = (char *)tvb_memdup(pinfo->pool, salt_tvb, 0, salt_size);

  if (pw == NULL)
    pwlen = 0;
  else
    pwlen = strlen(pw);

  if (pwlen > 63 / 2) {
    return false;
  }

  /* Store salt and password in BUF_I */
  p = buf_i;
  for (i = 0; i < 64; i++)
    *p++ = salt_p[i % salt_size];

  if (pw) {
    for (i = j = 0; i < 64; i += 2) {
      *p++ = 0;
      *p++ = pw[j];
      if (++j > pwlen)	/* Note, that we include the trailing zero */
        j = 0;
    }
  }
  else
    memset (p, 0, 64);

  for (;;) {
      err = gcry_md_open(&md, GCRY_MD_SHA1, 0);
      if (gcry_err_code(err)) {
        return false;
      }
      for (i = 0; i < 64; i++) {
        unsigned char lid = id & 0xFF;
        gcry_md_write (md, &lid, 1);
      }

      gcry_md_write(md, buf_i, pw ? 128 : 64);

      gcry_md_final (md);
      memcpy (hash, gcry_md_read (md, 0), 20);

      gcry_md_close (md);

      for (i = 1; i < iter; i++)
        gcry_md_hash_buffer (GCRY_MD_SHA1, hash, hash, 20);

      for (i = 0; i < 20 && cur_keylen < req_keylen; i++)
        keybuf[cur_keylen++] = hash[i];

      if (cur_keylen == req_keylen) {
        gcry_mpi_release (num_b1);
        return true;		/* ready */
      }

      /* need more bytes. */
      for (i = 0; i < 64; i++)
        buf_b[i] = hash[i % 20];

      n = 64;

      rc = gcry_mpi_scan (&num_b1, GCRYMPI_FMT_USG, buf_b, n, &n);

      if (rc != 0) {
        return false;
      }

      gcry_mpi_add_ui (num_b1, num_b1, 1);

      for (i = 0; i < 128; i += 64) {
        gcry_mpi_t num_ij;

        n = 64;
        rc = gcry_mpi_scan (&num_ij, GCRYMPI_FMT_USG, buf_i + i, n, &n);

        if (rc != 0) {
          return false;
        }

        gcry_mpi_add (num_ij, num_ij, num_b1);
        gcry_mpi_clear_highbit (num_ij, 64 * 8);

        n = 64;

        rc = gcry_mpi_print (GCRYMPI_FMT_USG, buf_i + i, n, &n, num_ij);
        if (rc != 0) {
          return false;
        }

        gcry_mpi_release (num_ij);
      }
  }
}

void PBE_reset_parameters(void)
{
	iteration_count = 0;
	salt = NULL;
}

int PBE_decrypt_data(dissector_t dissector, const char *description, tvbuff_t *encrypted_tvb, packet_info *pinfo, asn1_ctx_t *actx, proto_item *item)
{
	const char	*encryption_algorithm;
	gcry_cipher_hd_t cipher;
	gcry_error_t	err;
	int		algo;
	int		mode;
	int		ivlen = 0;
	int		keylen = 0;
	int		datalen = 0;
	char		*key = NULL;
	char		*iv = NULL;
	char		*clear_data = NULL;
	tvbuff_t	*clear_tvb = NULL;
	GString		*name;
	proto_tree	*tree;
	char		byte;
	bool	decrypt_ok = true;

	if(((password == NULL) || (*password == '\0')) && (try_null_password == false)) {
		/* we are not configured to decrypt */
		return false;
	}

	encryption_algorithm = x509af_get_last_algorithm_id();

	/* these are the only encryption schemes we understand for now */
	if(!strcmp(encryption_algorithm, PKCS12_PBE_3DES_SHA1_OID)) {
		ivlen = 8;
		keylen = 24;
		algo = GCRY_CIPHER_3DES;
		mode = GCRY_CIPHER_MODE_CBC;
	} else if(!strcmp(encryption_algorithm, PKCS12_PBE_ARCFOUR_SHA1_OID)) {
		ivlen = 0;
		keylen = 16;
		algo = GCRY_CIPHER_ARCFOUR;
		mode = GCRY_CIPHER_MODE_NONE;
	} else if(!strcmp(encryption_algorithm, PKCS12_PBE_RC2_40_SHA1_OID)) {
		ivlen = 8;
		keylen = 5;
		algo = GCRY_CIPHER_RFC2268_40;
		mode = GCRY_CIPHER_MODE_CBC;
	} else {
		/* we don't know how to decrypt this */

		proto_item_append_text(item, " [Unsupported encryption algorithm]");
		return false;
	}

	if((iteration_count == 0) || (salt == NULL)) {
		proto_item_append_text(item, " [Insufficient parameters]");
		return false;
	}

	/* allocate buffers */
	key = (char *)wmem_alloc(pinfo->pool, keylen);

	if(!generate_key_or_iv(pinfo, 1 /*LEY */, salt, iteration_count, password, keylen, key))
		return false;

	if(ivlen) {

		iv = (char *)wmem_alloc(pinfo->pool, ivlen);

		if(!generate_key_or_iv(pinfo, 2 /* IV */, salt, iteration_count, password, ivlen, iv))
			return false;
	}

	/* now try an internal function */
	err = gcry_cipher_open(&cipher, algo, mode, 0);
	if (gcry_err_code (err))
			return false;

	err = gcry_cipher_setkey (cipher, key, keylen);
	if (gcry_err_code (err)) {
			gcry_cipher_close (cipher);
			return false;
	}

	if(ivlen) {
		  err = gcry_cipher_setiv (cipher, iv, ivlen);
		  if (gcry_err_code (err)) {
			  gcry_cipher_close (cipher);
			  return false;
		  }
	}

	datalen = tvb_captured_length(encrypted_tvb);
	clear_data = (char *)wmem_alloc(pinfo->pool, datalen);

	err = gcry_cipher_decrypt (cipher, clear_data, datalen, (char *)tvb_memdup(pinfo->pool, encrypted_tvb, 0, datalen), datalen);
	if (gcry_err_code (err)) {

		proto_item_append_text(item, " [Failed to decrypt with password preference]");

		gcry_cipher_close (cipher);
		return false;
	}

	gcry_cipher_close (cipher);

	/* We don't know if we have successfully decrypted the data or not so we:
		a) check the trailing bytes
		b) see if we start with a sequence or a set (is this too constraining?
		*/

	/* first the trailing bytes */
	byte = clear_data[datalen-1];
	if(byte <= 0x08) {
		int i;

		for(i = (int)byte; i > 0 ; i--) {
			if(clear_data[datalen - i] != byte) {
				decrypt_ok = false;
				break;
			}
		}
	} else {
		/* XXX: is this a failure? */
	}

	/* we assume the result is ASN.1 - check it is a SET or SEQUENCE */
	byte = clear_data[0];
	if((byte != 0x30) && (byte != 0x31)) { /* do we need more here? OCTET STRING? */
		decrypt_ok = false;
	}

	if(!decrypt_ok) {
		proto_item_append_text(item, " [Failed to decrypt with supplied password]");

		return false;
	}

	proto_item_append_text(item, " [Decrypted successfully]");

	tree = proto_item_add_subtree(item, ett_decrypted_pbe);

	/* OK - so now clear_data contains the decrypted data */

	clear_tvb = tvb_new_child_real_data(encrypted_tvb,(const uint8_t *)clear_data, datalen, datalen);

	name = g_string_new("");
	g_string_printf(name, "Decrypted %s", description);

	/* add it as a new source */
	add_new_data_source(actx->pinfo, clear_tvb, name->str);

	g_string_free(name, TRUE);

	/* now try and decode it */
	dissector(clear_tvb, actx->pinfo, tree, NULL);

	return true;
}


static const value_string pkcs12_T_version_vals[] = {
  {   3, "v3" },
  { 0, NULL }
};


static int
dissect_pkcs12_T_version(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_integer(implicit_tag, actx, tree, tvb, offset, hf_index,
                                                NULL);

  return offset;
}



static int
dissect_pkcs12_OCTET_STRING(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_octet_string(implicit_tag, actx, tree, tvb, offset, hf_index,
                                       (hf_index == hf_pkcs12_salt ? &salt : NULL));

  return offset;
}



static int
dissect_pkcs12_INTEGER(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_integer(implicit_tag, actx, tree, tvb, offset, hf_index,
                                                (hf_index == hf_pkcs12_iterations ? &iteration_count : NULL));

  return offset;
}


static const ber_sequence_t MacData_sequence[] = {
  { &hf_pkcs12_mac          , BER_CLASS_UNI, BER_UNI_TAG_SEQUENCE, BER_FLAGS_NOOWNTAG, dissect_cms_DigestInfo },
  { &hf_pkcs12_macSalt      , BER_CLASS_UNI, BER_UNI_TAG_OCTETSTRING, BER_FLAGS_NOOWNTAG, dissect_pkcs12_OCTET_STRING },
  { &hf_pkcs12_iterations   , BER_CLASS_UNI, BER_UNI_TAG_INTEGER, BER_FLAGS_OPTIONAL|BER_FLAGS_NOOWNTAG, dissect_pkcs12_INTEGER },
  { NULL, 0, 0, 0, NULL }
};

static int
dissect_pkcs12_MacData(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_sequence(implicit_tag, actx, tree, tvb, offset,
                                   MacData_sequence, hf_index, ett_pkcs12_MacData);

  return offset;
}


static const ber_sequence_t PFX_sequence[] = {
  { &hf_pkcs12_version      , BER_CLASS_UNI, BER_UNI_TAG_INTEGER, BER_FLAGS_NOOWNTAG, dissect_pkcs12_T_version },
  { &hf_pkcs12_authSafe     , BER_CLASS_UNI, BER_UNI_TAG_SEQUENCE, BER_FLAGS_NOOWNTAG, dissect_cms_ContentInfo },
  { &hf_pkcs12_macData      , BER_CLASS_UNI, BER_UNI_TAG_SEQUENCE, BER_FLAGS_OPTIONAL|BER_FLAGS_NOOWNTAG, dissect_pkcs12_MacData },
  { NULL, 0, 0, 0, NULL }
};

static int
dissect_pkcs12_PFX(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
	dissector_handle_t dissector_handle;

	/* we change the CMS id-data dissector to dissect as AuthenticatedSafe
	   not sure why PKCS#12 couldn't have used its own content type OID for AuthenticatedSafe */
	dissector_handle=create_dissector_handle(dissect_AuthenticatedSafe_OCTETSTRING_PDU, proto_pkcs12);
	dissector_change_string("ber.oid", "1.2.840.113549.1.7.1", dissector_handle);

	  offset = dissect_ber_sequence(implicit_tag, actx, tree, tvb, offset,
                                   PFX_sequence, hf_index, ett_pkcs12_PFX);


	/* restore the original dissector */
	dissector_reset_string("ber.oid", "1.2.840.113549.1.7.1");


  return offset;
}


static const ber_sequence_t AuthenticatedSafe_sequence_of[1] = {
  { &hf_pkcs12_AuthenticatedSafe_item, BER_CLASS_UNI, BER_UNI_TAG_SEQUENCE, BER_FLAGS_NOOWNTAG, dissect_cms_ContentInfo },
};

static int
dissect_pkcs12_AuthenticatedSafe(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
	dissector_handle_t dissector_handle;

	/* we change the CMS id-data dissector to dissect as SafeContents */
	dissector_handle=create_dissector_handle(dissect_SafeContents_OCTETSTRING_PDU, proto_pkcs12);
	dissector_change_string("ber.oid", "1.2.840.113549.1.7.1", dissector_handle);

	  offset = dissect_ber_sequence_of(implicit_tag, actx, tree, tvb, offset,
                                      AuthenticatedSafe_sequence_of, hf_index, ett_pkcs12_AuthenticatedSafe);


	/* restore the original dissector */
	dissector_reset_string("ber.oid", "1.2.840.113549.1.7.1");


  return offset;
}



static int
dissect_pkcs12_T_bagId(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_object_identifier_str(implicit_tag, actx, tree, tvb, offset, hf_index, &object_identifier_id);

  append_oid(actx->pinfo->pool, tree, object_identifier_id);
  return offset;
}



static int
dissect_pkcs12_T_bagValue(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
	if(object_identifier_id)
		offset = call_ber_oid_callback(object_identifier_id, tvb, offset, actx->pinfo, tree, NULL);


  return offset;
}



static int
dissect_pkcs12_T_attrId(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_object_identifier_str(implicit_tag, actx, tree, tvb, offset, hf_index, &object_identifier_id);

  append_oid(actx->pinfo->pool, tree, object_identifier_id);
  return offset;
}



static int
dissect_pkcs12_T_attrValues_item(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
	if(object_identifier_id)
		offset = call_ber_oid_callback(object_identifier_id, tvb, offset, actx->pinfo, tree, NULL);


  return offset;
}


static const ber_sequence_t T_attrValues_set_of[1] = {
  { &hf_pkcs12_attrValues_item, BER_CLASS_ANY, 0, BER_FLAGS_NOOWNTAG, dissect_pkcs12_T_attrValues_item },
};

static int
dissect_pkcs12_T_attrValues(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_set_of(implicit_tag, actx, tree, tvb, offset,
                                 T_attrValues_set_of, hf_index, ett_pkcs12_T_attrValues);

  return offset;
}


static const ber_sequence_t PKCS12Attribute_sequence[] = {
  { &hf_pkcs12_attrId       , BER_CLASS_UNI, BER_UNI_TAG_OID, BER_FLAGS_NOOWNTAG, dissect_pkcs12_T_attrId },
  { &hf_pkcs12_attrValues   , BER_CLASS_UNI, BER_UNI_TAG_SET, BER_FLAGS_NOOWNTAG, dissect_pkcs12_T_attrValues },
  { NULL, 0, 0, 0, NULL }
};

static int
dissect_pkcs12_PKCS12Attribute(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_sequence(implicit_tag, actx, tree, tvb, offset,
                                   PKCS12Attribute_sequence, hf_index, ett_pkcs12_PKCS12Attribute);

  return offset;
}


static const ber_sequence_t SET_OF_PKCS12Attribute_set_of[1] = {
  { &hf_pkcs12_bagAttributes_item, BER_CLASS_UNI, BER_UNI_TAG_SEQUENCE, BER_FLAGS_NOOWNTAG, dissect_pkcs12_PKCS12Attribute },
};

static int
dissect_pkcs12_SET_OF_PKCS12Attribute(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_set_of(implicit_tag, actx, tree, tvb, offset,
                                 SET_OF_PKCS12Attribute_set_of, hf_index, ett_pkcs12_SET_OF_PKCS12Attribute);

  return offset;
}


static const ber_sequence_t SafeBag_sequence[] = {
  { &hf_pkcs12_bagId        , BER_CLASS_UNI, BER_UNI_TAG_OID, BER_FLAGS_NOOWNTAG, dissect_pkcs12_T_bagId },
  { &hf_pkcs12_bagValue     , BER_CLASS_CON, 0, 0, dissect_pkcs12_T_bagValue },
  { &hf_pkcs12_bagAttributes, BER_CLASS_UNI, BER_UNI_TAG_SET, BER_FLAGS_OPTIONAL|BER_FLAGS_NOOWNTAG, dissect_pkcs12_SET_OF_PKCS12Attribute },
  { NULL, 0, 0, 0, NULL }
};

static int
dissect_pkcs12_SafeBag(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_sequence(implicit_tag, actx, tree, tvb, offset,
                                   SafeBag_sequence, hf_index, ett_pkcs12_SafeBag);

  return offset;
}


static const ber_sequence_t SafeContents_sequence_of[1] = {
  { &hf_pkcs12_SafeContents_item, BER_CLASS_UNI, BER_UNI_TAG_SEQUENCE, BER_FLAGS_NOOWNTAG, dissect_pkcs12_SafeBag },
};

static int
dissect_pkcs12_SafeContents(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_sequence_of(implicit_tag, actx, tree, tvb, offset,
                                      SafeContents_sequence_of, hf_index, ett_pkcs12_SafeContents);

  return offset;
}



static int
dissect_pkcs12_KeyBag(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_akp_PrivateKeyInfo(implicit_tag, tvb, offset, actx, tree, hf_index);

  return offset;
}



static int
dissect_pkcs12_PKCS8ShroudedKeyBag(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_akp_EncryptedPrivateKeyInfo(implicit_tag, tvb, offset, actx, tree, hf_index);

  return offset;
}



static int
dissect_pkcs12_T_certId(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_object_identifier_str(implicit_tag, actx, tree, tvb, offset, hf_index, &object_identifier_id);

  append_oid(actx->pinfo->pool, tree, object_identifier_id);
  return offset;
}



static int
dissect_pkcs12_T_certValue(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
	if(object_identifier_id)
		offset = call_ber_oid_callback(object_identifier_id, tvb, offset, actx->pinfo, tree, NULL);


  return offset;
}


static const ber_sequence_t CertBag_sequence[] = {
  { &hf_pkcs12_certId       , BER_CLASS_UNI, BER_UNI_TAG_OID, BER_FLAGS_NOOWNTAG, dissect_pkcs12_T_certId },
  { &hf_pkcs12_certValue    , BER_CLASS_CON, 0, 0, dissect_pkcs12_T_certValue },
  { NULL, 0, 0, 0, NULL }
};

static int
dissect_pkcs12_CertBag(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_sequence(implicit_tag, actx, tree, tvb, offset,
                                   CertBag_sequence, hf_index, ett_pkcs12_CertBag);

  return offset;
}



static int
dissect_pkcs12_T_crlId(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_object_identifier_str(implicit_tag, actx, tree, tvb, offset, hf_index, &object_identifier_id);

  append_oid(actx->pinfo->pool, tree, object_identifier_id);
  return offset;
}



static int
dissect_pkcs12_T_crlValue(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
	if(object_identifier_id)
		offset = call_ber_oid_callback(object_identifier_id, tvb, offset, actx->pinfo, tree, NULL);


  return offset;
}


static const ber_sequence_t CRLBag_sequence[] = {
  { &hf_pkcs12_crlId        , BER_CLASS_UNI, BER_UNI_TAG_OID, BER_FLAGS_NOOWNTAG, dissect_pkcs12_T_crlId },
  { &hf_pkcs12_crlValue     , BER_CLASS_CON, 0, 0, dissect_pkcs12_T_crlValue },
  { NULL, 0, 0, 0, NULL }
};

static int
dissect_pkcs12_CRLBag(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_sequence(implicit_tag, actx, tree, tvb, offset,
                                   CRLBag_sequence, hf_index, ett_pkcs12_CRLBag);

  return offset;
}



static int
dissect_pkcs12_T_secretTypeId(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_object_identifier_str(implicit_tag, actx, tree, tvb, offset, hf_index, &object_identifier_id);

  append_oid(actx->pinfo->pool, tree, object_identifier_id);
  return offset;
}



static int
dissect_pkcs12_T_secretValue(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
	if(object_identifier_id)
		offset = call_ber_oid_callback(object_identifier_id, tvb, offset, actx->pinfo, tree, NULL);


  return offset;
}


static const ber_sequence_t SecretBag_sequence[] = {
  { &hf_pkcs12_secretTypeId , BER_CLASS_UNI, BER_UNI_TAG_OID, BER_FLAGS_NOOWNTAG, dissect_pkcs12_T_secretTypeId },
  { &hf_pkcs12_secretValue  , BER_CLASS_CON, 0, 0, dissect_pkcs12_T_secretValue },
  { NULL, 0, 0, 0, NULL }
};

static int
dissect_pkcs12_SecretBag(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_sequence(implicit_tag, actx, tree, tvb, offset,
                                   SecretBag_sequence, hf_index, ett_pkcs12_SecretBag);

  return offset;
}


static const ber_sequence_t Pkcs_12PbeParams_sequence[] = {
  { &hf_pkcs12_salt         , BER_CLASS_UNI, BER_UNI_TAG_OCTETSTRING, BER_FLAGS_NOOWNTAG, dissect_pkcs12_OCTET_STRING },
  { &hf_pkcs12_iterations   , BER_CLASS_UNI, BER_UNI_TAG_INTEGER, BER_FLAGS_NOOWNTAG, dissect_pkcs12_INTEGER },
  { NULL, 0, 0, 0, NULL }
};

static int
dissect_pkcs12_Pkcs_12PbeParams(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
	/* initialise the encryption parameters */
	PBE_reset_parameters();

  offset = dissect_ber_sequence(implicit_tag, actx, tree, tvb, offset,
                                   Pkcs_12PbeParams_sequence, hf_index, ett_pkcs12_Pkcs_12PbeParams);

  return offset;
}


static const value_string pkcs12_T_saltChoice_vals[] = {
  {   0, "specified" },
  {   1, "otherSource" },
  { 0, NULL }
};

static const ber_choice_t T_saltChoice_choice[] = {
  {   0, &hf_pkcs12_specified    , BER_CLASS_UNI, BER_UNI_TAG_OCTETSTRING, BER_FLAGS_NOOWNTAG, dissect_pkcs12_OCTET_STRING },
  {   1, &hf_pkcs12_otherSource  , BER_CLASS_UNI, BER_UNI_TAG_SEQUENCE, BER_FLAGS_NOOWNTAG, dissect_x509af_AlgorithmIdentifier },
  { 0, NULL, 0, 0, 0, NULL }
};

static int
dissect_pkcs12_T_saltChoice(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_choice(actx, tree, tvb, offset,
                                 T_saltChoice_choice, hf_index, ett_pkcs12_T_saltChoice,
                                 NULL);

  return offset;
}



static int
dissect_pkcs12_INTEGER_1_MAX(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_integer64(implicit_tag, actx, tree, tvb, offset, hf_index,
                                                NULL);

  return offset;
}


static const ber_sequence_t PBKDF2_params_sequence[] = {
  { &hf_pkcs12_saltChoice   , BER_CLASS_ANY/*choice*/, -1/*choice*/, BER_FLAGS_NOOWNTAG|BER_FLAGS_NOTCHKTAG, dissect_pkcs12_T_saltChoice },
  { &hf_pkcs12_iterationCount, BER_CLASS_UNI, BER_UNI_TAG_INTEGER, BER_FLAGS_NOOWNTAG, dissect_pkcs12_INTEGER },
  { &hf_pkcs12_keyLength    , BER_CLASS_UNI, BER_UNI_TAG_INTEGER, BER_FLAGS_OPTIONAL|BER_FLAGS_NOOWNTAG, dissect_pkcs12_INTEGER_1_MAX },
  { &hf_pkcs12_prf          , BER_CLASS_UNI, BER_UNI_TAG_SEQUENCE, BER_FLAGS_OPTIONAL|BER_FLAGS_NOOWNTAG, dissect_x509af_AlgorithmIdentifier },
  { NULL, 0, 0, 0, NULL }
};

static int
dissect_pkcs12_PBKDF2_params(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_sequence(implicit_tag, actx, tree, tvb, offset,
                                   PBKDF2_params_sequence, hf_index, ett_pkcs12_PBKDF2_params);

  return offset;
}


static const ber_sequence_t PBEParameter_sequence[] = {
  { &hf_pkcs12_salt         , BER_CLASS_UNI, BER_UNI_TAG_OCTETSTRING, BER_FLAGS_NOOWNTAG, dissect_pkcs12_OCTET_STRING },
  { &hf_pkcs12_iterationCount, BER_CLASS_UNI, BER_UNI_TAG_INTEGER, BER_FLAGS_NOOWNTAG, dissect_pkcs12_INTEGER },
  { NULL, 0, 0, 0, NULL }
};

static int
dissect_pkcs12_PBEParameter(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_sequence(implicit_tag, actx, tree, tvb, offset,
                                   PBEParameter_sequence, hf_index, ett_pkcs12_PBEParameter);

  return offset;
}


static const ber_sequence_t PBES2_params_sequence[] = {
  { &hf_pkcs12_keyDerivationFunc, BER_CLASS_UNI, BER_UNI_TAG_SEQUENCE, BER_FLAGS_NOOWNTAG, dissect_x509af_AlgorithmIdentifier },
  { &hf_pkcs12_encryptionScheme, BER_CLASS_UNI, BER_UNI_TAG_SEQUENCE, BER_FLAGS_NOOWNTAG, dissect_x509af_AlgorithmIdentifier },
  { NULL, 0, 0, 0, NULL }
};

static int
dissect_pkcs12_PBES2_params(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_sequence(implicit_tag, actx, tree, tvb, offset,
                                   PBES2_params_sequence, hf_index, ett_pkcs12_PBES2_params);

  return offset;
}


static const ber_sequence_t PBMAC1_params_sequence[] = {
  { &hf_pkcs12_keyDerivationFunc, BER_CLASS_UNI, BER_UNI_TAG_SEQUENCE, BER_FLAGS_NOOWNTAG, dissect_x509af_AlgorithmIdentifier },
  { &hf_pkcs12_messageAuthScheme, BER_CLASS_UNI, BER_UNI_TAG_SEQUENCE, BER_FLAGS_NOOWNTAG, dissect_x509af_AlgorithmIdentifier },
  { NULL, 0, 0, 0, NULL }
};

static int
dissect_pkcs12_PBMAC1_params(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_sequence(implicit_tag, actx, tree, tvb, offset,
                                   PBMAC1_params_sequence, hf_index, ett_pkcs12_PBMAC1_params);

  return offset;
}


static const ber_sequence_t Scrypt_params_sequence[] = {
  { &hf_pkcs12_salt         , BER_CLASS_UNI, BER_UNI_TAG_OCTETSTRING, BER_FLAGS_NOOWNTAG, dissect_pkcs12_OCTET_STRING },
  { &hf_pkcs12_costParameter, BER_CLASS_UNI, BER_UNI_TAG_INTEGER, BER_FLAGS_NOOWNTAG, dissect_pkcs12_INTEGER_1_MAX },
  { &hf_pkcs12_blockSize    , BER_CLASS_UNI, BER_UNI_TAG_INTEGER, BER_FLAGS_NOOWNTAG, dissect_pkcs12_INTEGER_1_MAX },
  { &hf_pkcs12_parallelizationParameter, BER_CLASS_UNI, BER_UNI_TAG_INTEGER, BER_FLAGS_NOOWNTAG, dissect_pkcs12_INTEGER_1_MAX },
  { &hf_pkcs12_keyLength    , BER_CLASS_UNI, BER_UNI_TAG_INTEGER, BER_FLAGS_OPTIONAL|BER_FLAGS_NOOWNTAG, dissect_pkcs12_INTEGER_1_MAX },
  { NULL, 0, 0, 0, NULL }
};

static int
dissect_pkcs12_Scrypt_params(bool implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_ber_sequence(implicit_tag, actx, tree, tvb, offset,
                                   Scrypt_params_sequence, hf_index, ett_pkcs12_Scrypt_params);

  return offset;
}

/*--- PDUs ---*/

static int dissect_PFX_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_BER, true, pinfo);
  offset = dissect_pkcs12_PFX(false, tvb, offset, &asn1_ctx, tree, hf_pkcs12_PFX_PDU);
  return offset;
}
static int dissect_SafeContents_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_BER, true, pinfo);
  offset = dissect_pkcs12_SafeContents(false, tvb, offset, &asn1_ctx, tree, hf_pkcs12_SafeContents_PDU);
  return offset;
}
static int dissect_KeyBag_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_BER, true, pinfo);
  offset = dissect_pkcs12_KeyBag(false, tvb, offset, &asn1_ctx, tree, hf_pkcs12_KeyBag_PDU);
  return offset;
}
static int dissect_PKCS8ShroudedKeyBag_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_BER, true, pinfo);
  offset = dissect_pkcs12_PKCS8ShroudedKeyBag(false, tvb, offset, &asn1_ctx, tree, hf_pkcs12_PKCS8ShroudedKeyBag_PDU);
  return offset;
}
static int dissect_CertBag_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_BER, true, pinfo);
  offset = dissect_pkcs12_CertBag(false, tvb, offset, &asn1_ctx, tree, hf_pkcs12_CertBag_PDU);
  return offset;
}
static int dissect_CRLBag_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_BER, true, pinfo);
  offset = dissect_pkcs12_CRLBag(false, tvb, offset, &asn1_ctx, tree, hf_pkcs12_CRLBag_PDU);
  return offset;
}
static int dissect_SecretBag_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_BER, true, pinfo);
  offset = dissect_pkcs12_SecretBag(false, tvb, offset, &asn1_ctx, tree, hf_pkcs12_SecretBag_PDU);
  return offset;
}
static int dissect_Pkcs_12PbeParams_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_BER, true, pinfo);
  offset = dissect_pkcs12_Pkcs_12PbeParams(false, tvb, offset, &asn1_ctx, tree, hf_pkcs12_Pkcs_12PbeParams_PDU);
  return offset;
}
static int dissect_PBKDF2_params_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_BER, true, pinfo);
  offset = dissect_pkcs12_PBKDF2_params(false, tvb, offset, &asn1_ctx, tree, hf_pkcs12_PBKDF2_params_PDU);
  return offset;
}
static int dissect_PBEParameter_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_BER, true, pinfo);
  offset = dissect_pkcs12_PBEParameter(false, tvb, offset, &asn1_ctx, tree, hf_pkcs12_PBEParameter_PDU);
  return offset;
}
static int dissect_PBES2_params_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_BER, true, pinfo);
  offset = dissect_pkcs12_PBES2_params(false, tvb, offset, &asn1_ctx, tree, hf_pkcs12_PBES2_params_PDU);
  return offset;
}
static int dissect_PBMAC1_params_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_BER, true, pinfo);
  offset = dissect_pkcs12_PBMAC1_params(false, tvb, offset, &asn1_ctx, tree, hf_pkcs12_PBMAC1_params_PDU);
  return offset;
}
static int dissect_Scrypt_params_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_BER, true, pinfo);
  offset = dissect_pkcs12_Scrypt_params(false, tvb, offset, &asn1_ctx, tree, hf_pkcs12_Scrypt_params_PDU);
  return offset;
}


static int strip_octet_string(tvbuff_t *tvb)
{
  int8_t ber_class;
  bool pc, ind;
  int32_t tag;
  uint32_t len;
  int offset = 0;

  /* PKCS#7 encodes the content as OCTET STRING, whereas CMS is just any ANY */
  /* if we use CMS (rather than PKCS#7) - which we are - we need to strip the OCTET STRING tag */
  /* before proceeding */

  offset = get_ber_identifier(tvb, 0, &ber_class, &pc, &tag);
  offset = get_ber_length(tvb, offset, &len, &ind);

  if((ber_class == BER_CLASS_UNI) && (tag == BER_UNI_TAG_OCTETSTRING))
    return offset;

  return 0;

}

static int dissect_AuthenticatedSafe_OCTETSTRING_PDU(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void* data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_BER, true, pinfo);

  if((offset = strip_octet_string(tvb)) > 0)
    dissect_pkcs12_AuthenticatedSafe(false, tvb, offset, &asn1_ctx, tree, hf_pkcs12_AuthenticatedSafe_PDU);
  else
    proto_tree_add_expert(tree, pinfo, &ei_pkcs12_octet_string_expected, tvb, 0, 1);
  return tvb_captured_length(tvb);
}

static int dissect_SafeContents_OCTETSTRING_PDU(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void* data _U_)
{
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_BER, true, pinfo);

  offset = strip_octet_string(tvb);

  dissect_pkcs12_SafeContents(false, tvb, offset, &asn1_ctx, tree, hf_pkcs12_SafeContents_PDU);
  return tvb_captured_length(tvb);
}

static int dissect_X509Certificate_OCTETSTRING_PDU(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void* data _U_)
{
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_BER, true, pinfo);

  if((offset = strip_octet_string(tvb)) > 0)
	dissect_x509af_Certificate(false, tvb, offset, &asn1_ctx, tree, hf_pkcs12_X509Certificate_PDU);
  else
	proto_tree_add_expert(tree, pinfo, &ei_pkcs12_octet_string_expected, tvb, 0, 1);

  return tvb_captured_length(tvb);
}

/*--- proto_register_pkcs12 ----------------------------------------------*/
void proto_register_pkcs12(void) {

  /* List of fields */
  static hf_register_info hf[] = {
    { &hf_pkcs12_X509Certificate_PDU,
      { "X509Certificate", "pkcs12.X509Certificate",
        FT_NONE, BASE_NONE, NULL, 0,
        "pkcs12.X509Certificate", HFILL }},
    { &hf_pkcs12_AuthenticatedSafe_PDU,
      { "AuthenticatedSafe", "pkcs12.AuthenticatedSafe",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},

    { &hf_pkcs12_PFX_PDU,
      { "PFX", "pkcs12.PFX_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_SafeContents_PDU,
      { "SafeContents", "pkcs12.SafeContents",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_KeyBag_PDU,
      { "KeyBag", "pkcs12.KeyBag_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_PKCS8ShroudedKeyBag_PDU,
      { "PKCS8ShroudedKeyBag", "pkcs12.PKCS8ShroudedKeyBag_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_CertBag_PDU,
      { "CertBag", "pkcs12.CertBag_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_CRLBag_PDU,
      { "CRLBag", "pkcs12.CRLBag_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_SecretBag_PDU,
      { "SecretBag", "pkcs12.SecretBag_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_Pkcs_12PbeParams_PDU,
      { "Pkcs-12PbeParams", "pkcs12.Pkcs_12PbeParams_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_PBKDF2_params_PDU,
      { "PBKDF2-params", "pkcs12.PBKDF2_params_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_PBEParameter_PDU,
      { "PBEParameter", "pkcs12.PBEParameter_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_PBES2_params_PDU,
      { "PBES2-params", "pkcs12.PBES2_params_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_PBMAC1_params_PDU,
      { "PBMAC1-params", "pkcs12.PBMAC1_params_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_Scrypt_params_PDU,
      { "Scrypt-params", "pkcs12.Scrypt_params_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_version,
      { "version", "pkcs12.version",
        FT_UINT32, BASE_DEC, VALS(pkcs12_T_version_vals), 0,
        NULL, HFILL }},
    { &hf_pkcs12_authSafe,
      { "authSafe", "pkcs12.authSafe_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "ContentInfo", HFILL }},
    { &hf_pkcs12_macData,
      { "macData", "pkcs12.macData_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_mac,
      { "mac", "pkcs12.mac_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "DigestInfo", HFILL }},
    { &hf_pkcs12_macSalt,
      { "macSalt", "pkcs12.macSalt",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING", HFILL }},
    { &hf_pkcs12_iterations,
      { "iterations", "pkcs12.iterations",
        FT_INT32, BASE_DEC, NULL, 0,
        "INTEGER", HFILL }},
    { &hf_pkcs12_AuthenticatedSafe_item,
      { "ContentInfo", "pkcs12.ContentInfo_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_SafeContents_item,
      { "SafeBag", "pkcs12.SafeBag_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_bagId,
      { "bagId", "pkcs12.bagId",
        FT_OID, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_bagValue,
      { "bagValue", "pkcs12.bagValue_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_bagAttributes,
      { "bagAttributes", "pkcs12.bagAttributes",
        FT_UINT32, BASE_DEC, NULL, 0,
        "SET_OF_PKCS12Attribute", HFILL }},
    { &hf_pkcs12_bagAttributes_item,
      { "PKCS12Attribute", "pkcs12.PKCS12Attribute_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_certId,
      { "certId", "pkcs12.certId",
        FT_OID, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_certValue,
      { "certValue", "pkcs12.certValue_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_crlId,
      { "crlId", "pkcs12.crlId",
        FT_OID, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_crlValue,
      { "crlValue", "pkcs12.crlValue_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_secretTypeId,
      { "secretTypeId", "pkcs12.secretTypeId",
        FT_OID, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_secretValue,
      { "secretValue", "pkcs12.secretValue_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_attrId,
      { "attrId", "pkcs12.attrId",
        FT_OID, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_attrValues,
      { "attrValues", "pkcs12.attrValues",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_attrValues_item,
      { "attrValues item", "pkcs12.attrValues_item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_pkcs12_salt,
      { "salt", "pkcs12.salt",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING", HFILL }},
    { &hf_pkcs12_saltChoice,
      { "salt", "pkcs12.saltChoice",
        FT_UINT32, BASE_DEC, VALS(pkcs12_T_saltChoice_vals), 0,
        "T_saltChoice", HFILL }},
    { &hf_pkcs12_specified,
      { "specified", "pkcs12.specified",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING", HFILL }},
    { &hf_pkcs12_otherSource,
      { "otherSource", "pkcs12.otherSource_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "AlgorithmIdentifier", HFILL }},
    { &hf_pkcs12_iterationCount,
      { "iterationCount", "pkcs12.iterationCount",
        FT_INT32, BASE_DEC, NULL, 0,
        "INTEGER", HFILL }},
    { &hf_pkcs12_keyLength,
      { "keyLength", "pkcs12.keyLength",
        FT_UINT64, BASE_DEC, NULL, 0,
        "INTEGER_1_MAX", HFILL }},
    { &hf_pkcs12_prf,
      { "prf", "pkcs12.prf_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "AlgorithmIdentifier", HFILL }},
    { &hf_pkcs12_keyDerivationFunc,
      { "keyDerivationFunc", "pkcs12.keyDerivationFunc_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "AlgorithmIdentifier", HFILL }},
    { &hf_pkcs12_encryptionScheme,
      { "encryptionScheme", "pkcs12.encryptionScheme_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "AlgorithmIdentifier", HFILL }},
    { &hf_pkcs12_messageAuthScheme,
      { "messageAuthScheme", "pkcs12.messageAuthScheme_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "AlgorithmIdentifier", HFILL }},
    { &hf_pkcs12_costParameter,
      { "costParameter", "pkcs12.costParameter",
        FT_UINT64, BASE_DEC, NULL, 0,
        "INTEGER_1_MAX", HFILL }},
    { &hf_pkcs12_blockSize,
      { "blockSize", "pkcs12.blockSize",
        FT_UINT64, BASE_DEC, NULL, 0,
        "INTEGER_1_MAX", HFILL }},
    { &hf_pkcs12_parallelizationParameter,
      { "parallelizationParameter", "pkcs12.parallelizationParameter",
        FT_UINT64, BASE_DEC, NULL, 0,
        "INTEGER_1_MAX", HFILL }},
  };

  /* List of subtrees */
  static int *ett[] = {
	  &ett_decrypted_pbe,
    &ett_pkcs12_PFX,
    &ett_pkcs12_MacData,
    &ett_pkcs12_AuthenticatedSafe,
    &ett_pkcs12_SafeContents,
    &ett_pkcs12_SafeBag,
    &ett_pkcs12_SET_OF_PKCS12Attribute,
    &ett_pkcs12_CertBag,
    &ett_pkcs12_CRLBag,
    &ett_pkcs12_SecretBag,
    &ett_pkcs12_PKCS12Attribute,
    &ett_pkcs12_T_attrValues,
    &ett_pkcs12_Pkcs_12PbeParams,
    &ett_pkcs12_PBKDF2_params,
    &ett_pkcs12_T_saltChoice,
    &ett_pkcs12_PBEParameter,
    &ett_pkcs12_PBES2_params,
    &ett_pkcs12_PBMAC1_params,
    &ett_pkcs12_Scrypt_params,
  };
  static ei_register_info ei[] = {
      { &ei_pkcs12_octet_string_expected, { "pkcs12.octet_string_expected", PI_PROTOCOL, PI_WARN, "BER Error: OCTET STRING expected", EXPFILL }},
  };

  module_t *pkcs12_module;
  expert_module_t* expert_pkcs12;

  /* Register protocol */
  proto_pkcs12 = proto_register_protocol(PNAME, PSNAME, PFNAME);

  /* Register fields and subtrees */
  proto_register_field_array(proto_pkcs12, hf, array_length(hf));
  proto_register_subtree_array(ett, array_length(ett));
  expert_pkcs12 = expert_register_protocol(proto_pkcs12);
  expert_register_field_array(expert_pkcs12, ei, array_length(ei));

  /* Register preferences */
  pkcs12_module = prefs_register_protocol(proto_pkcs12, NULL);

  prefs_register_string_preference(pkcs12_module, "password",
	"Password to decrypt the file with",
	"The password to used to decrypt the encrypted elements within"
	" the PKCS#12 file", &password);

  prefs_register_bool_preference(pkcs12_module, "try_null_password",
	"Try to decrypt with a empty password",
	"Whether to try and decrypt the encrypted data within the"
	" PKCS#12 with a NULL password", &try_null_password);

  register_ber_syntax_dissector("PKCS#12", proto_pkcs12, dissect_PFX_PDU);
  register_ber_oid_syntax(".p12", NULL, "PKCS#12");
  register_ber_oid_syntax(".pfx", NULL, "PKCS#12");
}


/*--- proto_reg_handoff_pkcs12 -------------------------------------------*/
void proto_reg_handoff_pkcs12(void) {
  register_ber_oid_dissector("1.2.840.113549.1.12.10.1.1", dissect_KeyBag_PDU, proto_pkcs12, "keyBag");
  register_ber_oid_dissector("1.2.840.113549.1.12.10.1.2", dissect_PKCS8ShroudedKeyBag_PDU, proto_pkcs12, "pkcs8ShroudedKeyBag");
  register_ber_oid_dissector("1.2.840.113549.1.12.10.1.3", dissect_CertBag_PDU, proto_pkcs12, "certBag");
  register_ber_oid_dissector("1.2.840.113549.1.12.10.1.4", dissect_SecretBag_PDU, proto_pkcs12, "secretBag");
  register_ber_oid_dissector("1.2.840.113549.1.12.10.1.5", dissect_CRLBag_PDU, proto_pkcs12, "crlBag");
  register_ber_oid_dissector("1.2.840.113549.1.12.10.1.6", dissect_SafeContents_PDU, proto_pkcs12, "safeContentsBag");
  register_ber_oid_dissector("2.16.840.1.113730.3.1.216", dissect_PFX_PDU, proto_pkcs12, "pkcs-9-at-PKCS12");
  register_ber_oid_dissector("1.2.840.113549.1.12.1.1", dissect_Pkcs_12PbeParams_PDU, proto_pkcs12, "pbeWithSHAAnd128BitRC4");
  register_ber_oid_dissector("1.2.840.113549.1.12.1.2", dissect_Pkcs_12PbeParams_PDU, proto_pkcs12, "pbeWithSHAAnd40BitRC4");
  register_ber_oid_dissector("1.2.840.113549.1.12.1.3", dissect_Pkcs_12PbeParams_PDU, proto_pkcs12, "pbeWithSHAAnd3-KeyTripleDES-CBC");
  register_ber_oid_dissector("1.2.840.113549.1.12.1.4", dissect_Pkcs_12PbeParams_PDU, proto_pkcs12, "pbeWithSHAAnd2-KeyTripleDES-CBC");
  register_ber_oid_dissector("1.2.840.113549.1.12.1.5", dissect_Pkcs_12PbeParams_PDU, proto_pkcs12, "pbeWithSHAAnd128BitRC2-CBC");
  register_ber_oid_dissector("1.2.840.113549.1.12.1.6", dissect_Pkcs_12PbeParams_PDU, proto_pkcs12, "pbeWithSHAAnd40BitRC2-CBC");
  register_ber_oid_dissector("1.2.840.113549.1.5.1", dissect_PBEParameter_PDU, proto_pkcs12, "pbeWithMD2AndDES-CBC");
  register_ber_oid_dissector("1.2.840.113549.1.5.3", dissect_PBEParameter_PDU, proto_pkcs12, "pbeWithMD5AndDES-CBC");
  register_ber_oid_dissector("1.2.840.113549.1.5.4", dissect_PBEParameter_PDU, proto_pkcs12, "pbeWithMD2AndRC2-CBC");
  register_ber_oid_dissector("1.2.840.113549.1.5.6", dissect_PBEParameter_PDU, proto_pkcs12, "pbeWithMD5AndRC2-CBC");
  register_ber_oid_dissector("1.2.840.113549.1.5.10", dissect_PBEParameter_PDU, proto_pkcs12, "pbeWithSHA1AndDES-CBC");
  register_ber_oid_dissector("1.2.840.113549.1.5.11", dissect_PBEParameter_PDU, proto_pkcs12, "pbeWithSHA1AndRC2-CBC");
  register_ber_oid_dissector("1.2.840.113549.1.5.12", dissect_PBKDF2_params_PDU, proto_pkcs12, "id-PBKDF2");
  register_ber_oid_dissector("1.2.840.113549.1.5.13", dissect_PBES2_params_PDU, proto_pkcs12, "id-PBES2");
  register_ber_oid_dissector("1.2.840.113549.1.5.14", dissect_PBMAC1_params_PDU, proto_pkcs12, "id-PBMAC1");
  register_ber_oid_dissector("1.3.6.1.4.1.11591.4.11", dissect_Scrypt_params_PDU, proto_pkcs12, "id-scrypt");


	register_ber_oid_dissector("1.2.840.113549.1.9.22.1", dissect_X509Certificate_OCTETSTRING_PDU, proto_pkcs12, "x509Certificate");

	register_ber_oid_dissector("1.2.840.113549.2.7", dissect_ber_oid_NULL_callback, proto_pkcs12, "id-hmacWithSHA1");
	register_ber_oid_dissector("1.2.840.113549.2.8", dissect_ber_oid_NULL_callback, proto_pkcs12, "id-hmacWithSHA224");
	register_ber_oid_dissector("1.2.840.113549.2.9", dissect_ber_oid_NULL_callback, proto_pkcs12, "id-hmacWithSHA256");
	register_ber_oid_dissector("1.2.840.113549.2.10", dissect_ber_oid_NULL_callback, proto_pkcs12, "id-hmacWithSHA384");
	register_ber_oid_dissector("1.2.840.113549.2.11", dissect_ber_oid_NULL_callback, proto_pkcs12, "id-hmacWithSHA512");
	register_ber_oid_dissector("1.2.840.113549.2.12", dissect_ber_oid_NULL_callback, proto_pkcs12, "id-hmacWithSHA512-224");
	register_ber_oid_dissector("1.2.840.113549.2.13", dissect_ber_oid_NULL_callback, proto_pkcs12, "id-hmacWithSHA512-256");
}

