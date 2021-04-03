/*
 * SPDX-FileCopyrightText: (c) 2003, 2004 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * SPDX-License-Identifier: BSD-1-Clause
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "RRLP-Components"
 *     found in "../rrlp-components.asn"
 */

#ifndef _GANSSSatelliteElement_H
#define _GANSSSatelliteElement_H

#include <asn_application.h>

/* Including external dependencies */
#include "GANSSClockModel.h"
#include "GANSSOrbitModel.h"
#include "SVID.h"
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /* GANSSSatelliteElement */
    typedef struct GANSSSatelliteElement
    {
        SVID_t svID;
        long svHealth;
        long iod;
        GANSSClockModel_t ganssClockModel;
        GANSSOrbitModel_t ganssOrbitModel;
        /*
         * This type is extensible,
         * possible extensions are below.
         */

        /* Context for parsing across buffer boundaries */
        asn_struct_ctx_t _asn_ctx;
    } GANSSSatelliteElement_t;

    /* Implementation */
    extern asn_TYPE_descriptor_t asn_DEF_GANSSSatelliteElement;

#ifdef __cplusplus
}
#endif

#endif /* _GANSSSatelliteElement_H_ */
#include <asn_internal.h>
