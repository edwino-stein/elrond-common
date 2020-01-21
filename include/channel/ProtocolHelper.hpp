#if !defined  _ELROND_PROTOCOL_HELPER_HPP
#define _ELROND_PROTOCOL_HELPER_HPP

    /**
     * The head message structure:
     * Bytes | 0 | 1 ~ 4 | 5 | 6 ~ length |
     *         |     |     |     |
     *         |     |     |     +-------> Message body
     *         |     |     +-------------> Total channels
     *         |     +-------------------> Message sequence
     *         +-------------------------> Action
     *
     * The channel data structure: 3 bytes for each channel:
     * Byte | ... | +0 | +1 | +2 | ... |
     *         |    |    |    |     |
     *         |    |    |    |     +----> Next bytes
     *         |    |    |    +----------> Data low byte
     *         |    |    +---------------> Data high byte
     *         |    +--------------------> Channel index
     *         +-------------------------> Previous bytes
     */


    #define ELROND_PROTOCOL_HEADER_SIZE             6   // HEADER_SIZE -> (ACTION(1) + SEQUENCE(4) + TOTAL(1)) bytes

    #define ELROND_PROTOCOL_HEAD_BYTE_ACTION        0   // Action's byte --------------------------* One byte for action

    #define ELROND_PROTOCOL_HEAD_HWORD_HBYTE_SEQ    1   // Sequence's high byte of high word ------*
    #define ELROND_PROTOCOL_HEAD_HWORD_LBYTE_SEQ    2   // Sequence's low byte of high word  ------* Four bytes (dword)
    #define ELROND_PROTOCOL_HEAD_LWORD_HBYTE_SEQ    3   // Sequence's high byte of low word  ------* for packet sequence
    #define ELROND_PROTOCOL_HEAD_LWORD_LBYTE_SEQ    4   // Sequence's low byte of low word   ------*

    #define ELROND_PROTOCOL_TOTAL_CH_BYTE           5   // Total channels -------------------------* One byte

    #define ELROND_PROTOCOL_BODY_FIRST_BYTE         6   // Body first byte
    #define ELROND_PROTOCOL_BYTES_PER_CHANNEL       3   // Bytes per channel

    #define ELROND_PROTOCOL_ACTION_UPDATE_CHANNEL   0

    #define ELROND_PROTOCOL_CALC_BUFFER(totalCh) ELROND_PROTOCOL_HEADER_SIZE + (totalCh * ELROND_PROTOCOL_BYTES_PER_CHANNEL)
    #define ELROND_CALC_CH_OFFSET(i) ELROND_PROTOCOL_HEADER_SIZE + (i * ELROND_PROTOCOL_BYTES_PER_CHANNEL)

    #define ELROND_GET_CH_INDEX(b, o) b[o]
    #define ELROND_GET_CH_DATA_HB(b, o) b[o + 1]
    #define ELROND_GET_CH_DATA_LB(b, o) b[o + 2]

#endif
