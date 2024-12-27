// Macro to handle platform differences
#ifdef _WIN32
#define strerror_r(errnum, buf, buflen) strerror_s(buf, buflen, errnum)
#else
#define strerror_r(errnum, buf, buflen) strerror_r(errnum, buf, buflen)
#endif
#ifdef _WIN32
#define fopen_safe(file, mode) fopen_s(&file, mode)
#else
#define fopen_safe(file, mode) fopen(file, mode)
#endif
#define _POSIX_C_SOURCE 200112
#define _FILE_OFFSET_BITS 64
#define _CRT_SECURE_NO_WARNINGS

// Include Statements
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define Opcodes

// Arithmetic Operations
#define OPCODE_SET                                                             \
  0x01 // Load an immediate value into a register (MOV equivalent) - Genesis 1:5
       // (God appointed light)
#define OPCODE_GATHER                                                          \
  0x02 // Add two registers, store in result (ADD equivalent) - John 4:35 (The
       // fields are ripe)
#define OPCODE_REMOVE                                                          \
  0x03 // Subtract one register from another (SUB equivalent) - John 15:2 (Prune
       // for fruitfulness)
#define OPCODE_FRUIT                                                           \
  0x04 // Multiply two registers (MUL equivalent) - Genesis 26:12 (Reaped a
       // hundredfold)
#define OPCODE_PORTION                                                         \
  0x05 // Divide one register by another (DIV equivalent) - Luke 12:13 (Divide
       // the inheritance)
#define OPCODE_INCREMENT                                                       \
  0x06 // Increment a register by 1 (INC equivalent) - 2 Peter 3:18 (Grow in
       // grace)
#define OPCODE_DECREMENT                                                       \
  0x07 // Decrement a register by 1 (DEC equivalent) - Matthew 11:28 (Rest for
       // the weary)
#define OPCODE_BREAD_ADD                                                       \
  0x25 // Floating-point addition (FADD equivalent) - John 6:11 (He multiplied
       // the loaves)
#define OPCODE_DEBT_RELEASE                                                    \
  0x26 // Floating-point subtraction (FSUB equivalent) - Matthew 6:12 (Forgive
       // us our debts)
#define OPCODE_SEED_MULTIPLY                                                   \
  0x27 // Floating-point multiplication (FMUL equivalent) - Genesis 26:12
       // (Reaped a hundredfold)
#define OPCODE_PORTION_DIVIDE                                                  \
  0x28 // Floating-point division (FDIV equivalent) - Luke 12:13 (Divide the
       // inheritance)
#define OPCODE_REMAINDER                                                       \
  0x35 // Calculate remainder (MOD equivalent) - Leviticus 19:13 (Give what is
       // fair)
#define OPCODE_HARVEST_ADD                                                     \
  0x36 // Multiply and add (MAC equivalent) - John 4:35 (The fields are ripe for
       // harvest)

// Logical Operations
#define OPCODE_ALIGN                                                           \
  0x08 // Logical AND of two registers (AND equivalent) - Amos 3:3 (Walk
       // together in agreement)
#define OPCODE_OFFER                                                           \
  0x09 // Logical OR of two registers (OR equivalent) - Romans 12:1 (Offer
       // yourselves)
#define OPCODE_DISCERN                                                         \
  0x0A // Logical NOT of a register (NOT equivalent) - 1 Corinthians 2:14
       // (Discern spiritual truths)
#define OPCODE_REFINE_FIRE                                                     \
  0x0B // Logical XOR of two registers (XOR equivalent) - Zechariah 13:9
       // (Refining in fire)
#define OPCODE_LANTERN                                                         \
  0x21 // Logical shift left (SHL equivalent) - Psalm 119:105 (Your word is a
       // lamp)
#define OPCODE_TAPER                                                           \
  0x22 // Logical shift right (SHR equivalent) - Matthew 7:14 (The narrow path)
#define OPCODE_CYCLE_LEFT                                                      \
  0x23 // Rotate left (ROL equivalent) - Ecclesiastes 3:1 (A time for every
       // season)
#define OPCODE_CYCLE_RIGHT                                                     \
  0x24 // Rotate right (ROR equivalent) - Genesis 8:22 (While the earth remains,
       // cycles)
#define OPCODE_WORDS_COMPARE                                                   \
  0x29 // String comparison (STRCMP equivalent) - Proverbs 27:17 (Iron sharpens
       // iron)
#define OPCODE_WORDS_MEASURE                                                   \
  0x2A // Measure string length (STRLEN equivalent) - Psalm 90:12 (Teach us to
       // number our days)
#define OPCODE_WORDS_COPY                                                      \
  0x2B // Copy a string (STRCPY equivalent) - Deuteronomy 6:7 (Teach them to
       // your children)
#define OPCODE_LIGHT_CANDLE                                                    \
  0x52 // Set a specific bit (SET equivalent) - Matthew 5:15 (Do not hide your
       // light)
#define OPCODE_REMOVE_DROSS                                                    \
  0x53 // Clear a specific bit (CLR equivalent) - Proverbs 25:4 (Remove the
       // dross from silver)
#define OPCODE_TURN_HEART                                                      \
  0x54 // Toggle a specific bit (NOT equivalent) - Malachi 4:6 (Turning hearts)
#define OPCODE_SEEK_WORD                                                       \
  0x57 // Search within a string (STRSEARCH equivalent) - Matthew 7:7 (Seek, and
       // you shall find)

// Memory Operations
#define OPCODE_LAY_UP                                                          \
  0x0C // Store a register value into memory (MOV [addr], reg) - Matthew 6:20
       // (Lay up treasures)
#define OPCODE_RECALL                                                          \
  0x0D // Load a memory value into a register (MOV reg, [addr]) - Psalm 105:5
       // (Remember His wonders)
#define OPCODE_CLEAR                                                           \
  0x0E // Clear a memory location (ZERO equivalent) - Psalm 51:7 (Cleanse me,
       // and I shall be clean)
#define OPCODE_SWAP                                                            \
  0x0F // Swap the values of two registers (XCHG equivalent) - Isaiah 61:3
       // (Beauty for ashes)
#define OPCODE_STORE_HOUSE                                                     \
  0x30 // Push onto stack (PUSH equivalent) - Malachi 3:10 (Bring the whole
       // tithe into the storehouse)
#define OPCODE_DRAW_FROM_WELL                                                  \
  0x31 // Pop from stack (POP equivalent) - John 4:7 (Give me a drink from the
       // well)
#define OPCODE_PREPARE_PLACE                                                   \
  0x4B // Allocate memory dynamically (ALLOC equivalent) - John 14:2 (I go to
       // prepare a place)
#define OPCODE_RETURN_TO_DUST                                                  \
  0x4C // Free allocated memory (FREE equivalent) - Genesis 3:19 (Dust you are,
       // and to dust you will return)

// Logical Comparison
#define OPCODE_WEIGH                                                           \
  0x32 // Compare values (CMP equivalent) - Daniel 5:27 (You have been weighed
       // and found wanting)

// Control Flow
#define OPCODE_WAIT                                                            \
  0x10 // Conditional branch if register is zero (JZ equivalent) - 1 Corinthians
       // 16:13 (Stand firm)
#define OPCODE_GO                                                              \
  0x11 // Unconditional branch to an address (JMP equivalent) - Exodus 14:15 (Go
       // forward)
#define OPCODE_DIAGNOSE                                                        \
  0x12 // Run a diagnostic pass (NOP/DIAG equivalent) - Psalm 139:23 (Search me,
       // God)
#define OPCODE_CALL                                                            \
  0x13 // Call a subroutine (CALL equivalent) - Isaiah 43:1 (I have called you
       // by name)
#define OPCODE_RETURN                                                          \
  0x14 // Return from a subroutine (RET equivalent) - Joel 2:25 (Restore what
       // was lost)
#define OPCODE_TRUST                                                           \
  0x33 // Conditional jump if truth (JE equivalent) - Proverbs 3:5 (Trust in the
       // Lord)
#define OPCODE_AVOID                                                           \
  0x34 // Conditional jump if not (JNE equivalent) - 1 Corinthians 10:14 (Flee
       // from idolatry)
#define OPCODE_WAIT_IN_FAITH                                                   \
  0x37 // Pause for divine timing (WAIT equivalent) - Isaiah 40:31 (Those who
       // wait on the Lord...)
#define OPCODE_COMPLETE_JOURNEY                                                \
  0x38 // Terminate execution (EXIT equivalent) - 2 Timothy 4:7 (I have finished
       // the race)
#define OPCODE_LIFT_UP                                                         \
  0x3D // Jump if greater than (JG equivalent) - Psalm 3:3 (You are the lifter
       // of my head)
#define OPCODE_BOW_DOWN                                                        \
  0x3C // Jump if less than (JL equivalent) - Proverbs 15:33 (Humility precedes
       // honor)
#define OPCODE_RISE_TO                                                         \
  0x50 // Jump if greater than or equal (JGE equivalent) - Psalm 61:2 (Lead me
       // to the rock)
#define OPCODE_FALL_TO                                                         \
  0x51 // Jump if less than or equal (JLE equivalent) - James 4:10 (Humble
       // yourselves)
#define OPCODE_END_RELATION                                                    \
  0xC0 // End execution (HLT equivalent) - Hebrews 8:13 (Make a new covenant)

// Debugging
#define OPCODE_EXAMINE_HEART                                                   \
  0x46 // Enable debugging/logging (DEBUG equivalent) - Psalm 139:23 (Search me,
       // God)
#define OPCODE_PAUSE_AND_CONSIDER                                              \
  0x47 // Pause execution for inspection (PAUSE equivalent) - Psalm 46:10 (Be
       // still and know)
#define OPCODE_HONOR_BOUNDARY                                                  \
  0x60 // Validate a value within a range (BOUND equivalent) - Proverbs 22:28
       // (Do not move an ancient boundary stone; honor the limits set by
       // ancestors)
#define OPCODE_SNARE_ESCAPE                                                    \
  0x61 // Gracefully recover from faults or exceptions (Exception handling
       // equivalent) - Psalm 91:3 (He will save you from the fowler's snare and
       // deadly pestilence)
#define OPCODE_PAUSE_PATH                                                      \
  0x67 // Set a breakpoint for debugging (BREAKPOINT equivalent) - Psalm 46:10
       // (Be still and know that I am God; pause and reflect)
#define OPCODE_SEARCH_DEPTH                                                    \
  0x68 // Examine a memory address or range (Memory inspection equivalent) - 1
       // Corinthians 11:28 (Let a person examine themselves to see if they
       // align with truth)

// Advanced Arithmetic
#define OPCODE_RAISE_UP                                                        \
  0x48 // Exponentiation (POW equivalent) - Exodus 17:11 (When Moses raised his
       // hands)
#define OPCODE_LAY_FLAT                                                        \
  0x49 // Square root (SQRT equivalent) - Isaiah 40:4 (Every valley shall be
       // raised up)
#define OPCODE_MEASURE_ANGLE                                                   \
  0x4A // Trigonometric functions (TRIG equivalent) - Job 38:5 (Who laid the
       // measurements?)
#define OPCODE_SEEK_DEPTH                                                      \
  0x55 // Compute logarithm (LOG equivalent) - Proverbs 20:5 (The purposes of a
       // person's heart are deep waters)
#define OPCODE_ASCEND_HIGHER                                                   \
  0x56 // Compute exponential (EXP equivalent) - Psalm 139:8 (If I ascend to the
       // heavens)

// Input/Output Handling
#define OPCODE_DRAW_WATER                                                      \
  0x4D // Read from input devices (READ equivalent) - Isaiah 12:3 (With joy you
       // will draw water)
#define OPCODE_POUR_OUT                                                        \
  0x4E // Write to output devices (WRITE equivalent) - Joel 2:28 (I will pour
       // out my Spirit)
#define OPCODE_DRAW_FROM_STREAM                                                \
  0x5A // Read from an I/O port (IN equivalent) - Isaiah 12:3 (With joy you will
       // draw water)
#define OPCODE_POUR_OUT_VESSEL                                                 \
  0x5B // Write to an I/O port (OUT equivalent) - Joel 2:28 (I will pour out my
       // Spirit)

// Synchronization and System
#define OPCODE_BIND                                                            \
  0x58 // Acquire a lock (LOCK equivalent) - Matthew 16:19 (Whatever you bind)
#define OPCODE_LOOSE                                                           \
  0x59 // Release a lock (UNLOCK equivalent) - Matthew 16:19 (Whatever you
       // loose)
#define OPCODE_TRUMPET_CALL                                                    \
  0x2C // Interrupt (INT equivalent) - Joel 2:1 (Blow the trumpet in Zion)
#define OPCODE_DIVINE_REQUEST                                                  \
  0x2D // System call (SYSCALL equivalent) - Philippians 4:6 (Let your requests
       // be made known)
#define OPCODE_SABBATH_REST                                                    \
  0x2E // Halt execution (HLT equivalent) - Hebrews 4:10 (Entered God's rest)
#define OPCODE_SOUND_TRUMPET                                                   \
  0x5D // Enable interrupts (STI equivalent) - Joel 2:1 (Blow the trumpet in
       // Zion)
#define OPCODE_SILENCE_TRUMPET                                                 \
  0x5E // Disable interrupts (CLI equivalent) - Ecclesiastes 3:7 (A time to be
       // silent)

// Communication and Data Flow
#define OPCODE_SEND_MESSAGE                                                    \
  0x18 // Send data to a network address (SEND equivalent) - Matthew 28:19 (Go
       // and make disciples of all nations)
#define OPCODE_RECEIVE_MESSAGE                                                 \
  0x19 // Receive data into a register (RECEIVE equivalent) - Matthew 13:23
       // (Those who receive the word)
#define OPCODE_DIVIDE_LABOR                                                    \
  0x1A // Divide a task among workers (FORK equivalent) - Nehemiah 4:16 (Divided
       // labor for building)
#define OPCODE_GAIN_WISDOM                                                     \
  0x1B // Store a learned relational pattern (LEARN equivalent) - Proverbs 9:9
       // (Teach the wise, and they will be wiser)
#define OPCODE_FORSAKE_MEMORY                                                  \
  0x1C // Erase a learned pattern (FORGET equivalent) - Isaiah 43:18 (Forget the
       // former things)
#define OPCODE_RESTORE_STATE                                                   \
  0x1D // Restore a corrupted state (RECOVER equivalent) - Joel 2:25 (I will
       // restore what was lost)
#define OPCODE_CENSUS_MARK                                                     \
  0x64 // Generate a hash value for data integrity (HASH equivalent) - Numbers
       // 1:2 (Take a census to account for each individual in the community)
#define OPCODE_PROCLAIM                                                        \
  0x69 // Send a message to all connected nodes (BROADCAST equivalent) - Matthew
       // 24:14 (The gospel of the kingdom will be preached to all the world)

// Security and Transformation
#define OPCODE_SEAL                                                            \
  0x1E // Encrypt data using a key (ENC equivalent) - Revelation 5:1 (A scroll,
       // sealed)
#define OPCODE_UNSEAL                                                          \
  0x1F // Decrypt data using a key (DEC equivalent) - Daniel 12:9 (Seal the book
       // until the end)

// Advanced Arithmetic and Matrix Operations
#define OPCODE_MULTIPLY_HARVEST                                                \
  0x20 // Multiply two matrices, store in result (MULMAT equivalent) - Acts 2:47
       // (The Lord added to their number daily)
#define OPCODE_INVERT_ORDER                                                    \
  0x65 // Compute the inverse of a matrix (Matrix inversion equivalent) -
       // Matthew 20:16 (The last shall be first, and the first last; reflect
       // inverse principles)
#define OPCODE_COUNT_BLESSINGS                                                 \
  0x66 // Calculate the sum of a series (Series summation equivalent) - Psalm
       // 139:17 (How precious are your thoughts, God! Vast is the sum of them)

// System-Level Operations
#define OPCODE_UNIFY_THREAD                                                    \
  0x62 // Create, pause, or terminate threads (THREAD equivalent) - Ecclesiastes
       // 4:12 (A cord of three strands is not easily broken; unity in action)
#define OPCODE_SEASON_SYNC                                                     \
  0x63 // Synchronize the system clock or timing (SYNC equivalent) -
       // Ecclesiastes 3:1 (To everything, there is a season and a time for
       // every purpose under heaven)

// AI and Relational Processing
#define OPCODE_DISCERN_PATTERN                                                 \
  0x6A // Run a relational pattern interpretation (INTERPRET equivalent) -
       // Genesis 41:16 (It is God who will give Pharaoh an answer through me)

// Define Registers

// General-Purpose Registers
#define REGISTER_A 0x01 // General-purpose
#define REGISTER_B 0x02 // General-purpose
#define REGISTER_C 0x03 // General-purpose
#define REGISTER_D 0x04 // General-purpose
#define REGISTER_E 0x05 // General-purpose
#define REGISTER_F 0x06 // General-purpose
#define REGISTER_G 0x07 // General-purpose
#define REGISTER_H 0x08 // General-purpose

// Special-Purpose Registers
#define REGISTER_IP 0x09  // Instruction Pointer
#define REGISTER_SP 0x0A  // Stack Pointer
#define REGISTER_FR 0x0B  // Flags Register
#define REGISTER_BP 0x0C  // Base Pointer
#define REGISTER_TMP 0x0D // Temporary register

// Vector Registers (Optional)
#define REGISTER_V0 0x0E // Vector register 0
#define REGISTER_V1 0x0F // Vector register 1

// Prototypes for Helper Functions
int validate_mnemonic(const char *mnemonic);
void handle_error(const char *message);
int expected_argument_count(const char *mnemonic);

// Create a 256-bit instruction structure
struct OmniCodeInstruction {
  uint8_t opcode;       // 8 bits - Operation code
  uint32_t operand1;    // 32 bits - First operand (register or immediate)
  uint32_t operand2;    // 32 bits - Second operand
  uint32_t operand3;    // 32 bits - Third operand
  uint64_t metadata;    // 64 bits - Relational Metadata (Scriptural Anchor)
  uint8_t reserved[11]; // 88 bits - Reserved for debugging, flags, or future
                        // extensions
};

// Function to create a 256-bit instruction with validation
struct OmniCodeInstruction create_instruction(uint8_t opcode, uint32_t operand1,
                                              uint32_t operand2,
                                              uint32_t operand3,
                                              uint64_t metadata) {
  if (opcode > 0xFF) {
    fprintf(stderr, "Error: Opcode exceeds 8-bit limit.\n");
    exit(EXIT_FAILURE);
  }
  if (operand1 > 0xFFFFFFFF || operand2 > 0xFFFFFFFF || operand3 > 0xFFFFFFFF) {
    fprintf(stderr, "Error: Operand exceeds 32-bit limit.\n");
    exit(EXIT_FAILURE);
  }

  struct OmniCodeInstruction instruction;
  instruction.opcode = opcode;
  instruction.operand1 = operand1;
  instruction.operand2 = operand2;
  instruction.operand3 = operand3;
  instruction.metadata = metadata;
  memset(instruction.reserved, 0, sizeof(instruction.reserved));

  return instruction;
}

// Function to encode metadata (improved hashing for uniqueness)
uint64_t encode_metadata(const char *text) {
  uint64_t hash = 0xcbf29ce484222325;       // FNV-1a 64-bit offset basis
  const uint64_t fnv_prime = 0x100000001b3; // FNV-1a 64-bit prime

  for (int i = 0; text[i] != '\0'; i++) {
    hash ^= (uint64_t)text[i];  // XOR with character
    hash *= fnv_prime;          // Multiply by FNV prime
    hash &= 0xFFFFFFFFFFFFFFFF; // Ensure 64-bit range
  }
  return hash;
}

// Assemble a NovaScript (.ns) file into an OmniCode binary (.oc)
void assemble(const char *input_file, const char *output_file, bool verbose) {
  FILE *infile = fopen(input_file, "r");
  FILE *outfile = fopen(output_file, "wb");
  if (!infile || !outfile) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  char line[256];
  int line_number = 0; // Track line numbers for better error reporting

  while (fgets(line, sizeof(line), infile)) {
    line_number++;
    struct OmniCodeInstruction instruction = {
        0}; // Initialize the instruction structure
    char mnemonic[32], arg1[32], arg2[32], arg3[32];
    int num_args = sscanf(line, "%s %s %s %s", mnemonic, arg1, arg2, arg3);

    // Initialize operands and metadata
    uint32_t operand1 = 0, operand2 = 0, operand3 = 0;
    uint64_t metadata = 0;

    // Handle comments and metadata
    char *comment_pos = strstr(line, ";");
    if (comment_pos) {
      if (strlen(comment_pos + 1) >
          1) { // Metadata exists if text follows the ;
        metadata = encode_metadata(comment_pos + 1); // Skip the ';'
      }
      *comment_pos = '\0'; // Null-terminate the line at the comment position
    }

    // Trim leading/trailing whitespace from the line
    char *trimmed_line = line;
    while (isspace(*trimmed_line))
      trimmed_line++;
    char *end = trimmed_line + strlen(trimmed_line) - 1;
    while (end > trimmed_line && isspace(*end))
      *end-- = '\0';

    // Skip empty lines or lines that only contained comments
    if (*trimmed_line == '\0')
      continue;

    // Match mnemonics to instructions
    if (strcmp(mnemonic, "SET") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = atoi(arg2); // Immediate value
      instruction =
          create_instruction(OPCODE_SET, operand1, operand2, 0, metadata);
    } else if (strcmp(mnemonic, "GATHER") == 0 && num_args == 4) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand3 = (strcmp(arg3, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg3, "B") == 0) ? REGISTER_B
                 : (strcmp(arg3, "C") == 0) ? REGISTER_C
                 : (strcmp(arg3, "D") == 0) ? REGISTER_D
                 : (strcmp(arg3, "E") == 0) ? REGISTER_E
                 : (strcmp(arg3, "F") == 0) ? REGISTER_F
                 : (strcmp(arg3, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction = create_instruction(OPCODE_GATHER, operand1, operand2,
                                       operand3, metadata);
    } else if (strcmp(mnemonic, "REMOVE") == 0 && num_args == 4) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand3 = (strcmp(arg3, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg3, "B") == 0) ? REGISTER_B
                 : (strcmp(arg3, "C") == 0) ? REGISTER_C
                 : (strcmp(arg3, "D") == 0) ? REGISTER_D
                 : (strcmp(arg3, "E") == 0) ? REGISTER_E
                 : (strcmp(arg3, "F") == 0) ? REGISTER_F
                 : (strcmp(arg3, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction = create_instruction(OPCODE_REMOVE, operand1, operand2,
                                       operand3, metadata);
    } else if (strcmp(mnemonic, "FRUIT") == 0 && num_args == 4) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand3 = (strcmp(arg3, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg3, "B") == 0) ? REGISTER_B
                 : (strcmp(arg3, "C") == 0) ? REGISTER_C
                 : (strcmp(arg3, "D") == 0) ? REGISTER_D
                 : (strcmp(arg3, "E") == 0) ? REGISTER_E
                 : (strcmp(arg3, "F") == 0) ? REGISTER_F
                 : (strcmp(arg3, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction = create_instruction(OPCODE_FRUIT, operand1, operand2,
                                       operand3, metadata);
    } else if (strcmp(mnemonic, "PORTION") == 0 && num_args == 4) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand3 = (strcmp(arg3, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg3, "B") == 0) ? REGISTER_B
                 : (strcmp(arg3, "C") == 0) ? REGISTER_C
                 : (strcmp(arg3, "D") == 0) ? REGISTER_D
                 : (strcmp(arg3, "E") == 0) ? REGISTER_E
                 : (strcmp(arg3, "F") == 0) ? REGISTER_F
                 : (strcmp(arg3, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction = create_instruction(OPCODE_PORTION, operand1, operand2,
                                       operand3, metadata);
    } else if (strcmp(mnemonic, "INCREMENT") == 0 && num_args == 2) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction =
          create_instruction(OPCODE_INCREMENT, operand1, 0, 0, metadata);
    } else if (strcmp(mnemonic, "DECREMENT") == 0 && num_args == 2) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction =
          create_instruction(OPCODE_DECREMENT, operand1, 0, 0, metadata);
    } else if (strcmp(mnemonic, "BREAD_ADD") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction =
          create_instruction(OPCODE_BREAD_ADD, operand1, operand2, 0, metadata);
    } else if (strcmp(mnemonic, "DEBT_RELEASE") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction = create_instruction(OPCODE_DEBT_RELEASE, operand1, operand2,
                                       0, metadata);
    } else if (strcmp(mnemonic, "SEED_MULTIPLY") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction = create_instruction(OPCODE_SEED_MULTIPLY, operand1, operand2,
                                       0, metadata);
    } else if (strcmp(mnemonic, "PORTION_DIVIDE") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction = create_instruction(OPCODE_PORTION_DIVIDE, operand1,
                                       operand2, 0, metadata);
    } else if (strcmp(mnemonic, "REMAINDER") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction =
          create_instruction(OPCODE_REMAINDER, operand1, operand2, 0, metadata);
    } else if (strcmp(mnemonic, "HARVEST_ADD") == 0 && num_args == 4) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand3 = (strcmp(arg3, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg3, "B") == 0) ? REGISTER_B
                 : (strcmp(arg3, "C") == 0) ? REGISTER_C
                 : (strcmp(arg3, "D") == 0) ? REGISTER_D
                 : (strcmp(arg3, "E") == 0) ? REGISTER_E
                 : (strcmp(arg3, "F") == 0) ? REGISTER_F
                 : (strcmp(arg3, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction = create_instruction(OPCODE_HARVEST_ADD, operand1, operand2,
                                       operand3, metadata);
    } else if (strcmp(mnemonic, "ALIGN") == 0 && num_args == 4) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand3 = (strcmp(arg3, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg3, "B") == 0) ? REGISTER_B
                 : (strcmp(arg3, "C") == 0) ? REGISTER_C
                 : (strcmp(arg3, "D") == 0) ? REGISTER_D
                 : (strcmp(arg3, "E") == 0) ? REGISTER_E
                 : (strcmp(arg3, "F") == 0) ? REGISTER_F
                 : (strcmp(arg3, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction = create_instruction(OPCODE_ALIGN, operand1, operand2,
                                       operand3, metadata);
    } else if (strcmp(mnemonic, "OFFER") == 0 && num_args == 4) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand3 = (strcmp(arg3, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg3, "B") == 0) ? REGISTER_B
                 : (strcmp(arg3, "C") == 0) ? REGISTER_C
                 : (strcmp(arg3, "D") == 0) ? REGISTER_D
                 : (strcmp(arg3, "E") == 0) ? REGISTER_E
                 : (strcmp(arg3, "F") == 0) ? REGISTER_F
                 : (strcmp(arg3, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction = create_instruction(OPCODE_OFFER, operand1, operand2,
                                       operand3, metadata);
    } else if (strcmp(mnemonic, "DISCERN") == 0 && num_args == 2) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction =
          create_instruction(OPCODE_DISCERN, operand1, 0, 0, metadata);
    } else if (strcmp(mnemonic, "REFINE_FIRE") == 0 && num_args == 4) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand3 = (strcmp(arg3, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg3, "B") == 0) ? REGISTER_B
                 : (strcmp(arg3, "C") == 0) ? REGISTER_C
                 : (strcmp(arg3, "D") == 0) ? REGISTER_D
                 : (strcmp(arg3, "E") == 0) ? REGISTER_E
                 : (strcmp(arg3, "F") == 0) ? REGISTER_F
                 : (strcmp(arg3, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction = create_instruction(OPCODE_REFINE_FIRE, operand1, operand2,
                                       operand3, metadata);
    } else if (strcmp(mnemonic, "LANTERN") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = atoi(arg2); // Shift amount (immediate value)
      instruction =
          create_instruction(OPCODE_LANTERN, operand1, operand2, 0, metadata);
    } else if (strcmp(mnemonic, "TAPER") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = atoi(arg2); // Shift amount (immediate value)
      instruction =
          create_instruction(OPCODE_TAPER, operand1, operand2, 0, metadata);
    } else if (strcmp(mnemonic, "CYCLE_LEFT") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = atoi(arg2); // Rotate amount (immediate value)
      instruction = create_instruction(OPCODE_CYCLE_LEFT, operand1, operand2, 0,
                                       metadata);
    } else if (strcmp(mnemonic, "CYCLE_RIGHT") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = atoi(arg2); // Rotate amount (immediate value)
      instruction = create_instruction(OPCODE_CYCLE_RIGHT, operand1, operand2,
                                       0, metadata);
    } else if (strcmp(mnemonic, "WORDS_COMPARE") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction = create_instruction(OPCODE_WORDS_COMPARE, operand1, operand2,
                                       0, metadata);
    } else if (strcmp(mnemonic, "WORDS_MEASURE") == 0 && num_args == 2) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction =
          create_instruction(OPCODE_WORDS_MEASURE, operand1, 0, 0, metadata);
    } else if (strcmp(mnemonic, "WORDS_COPY") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction = create_instruction(OPCODE_WORDS_COPY, operand1, operand2, 0,
                                       metadata);
    } else if (strcmp(mnemonic, "LIGHT_CANDLE") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = atoi(arg2); // Bit position (immediate value)
      instruction = create_instruction(OPCODE_LIGHT_CANDLE, operand1, operand2,
                                       0, metadata);
    } else if (strcmp(mnemonic, "REMOVE_DROSS") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = atoi(arg2); // Bit position (immediate value)
      instruction = create_instruction(OPCODE_REMOVE_DROSS, operand1, operand2,
                                       0, metadata);
    } else if (strcmp(mnemonic, "TURN_HEART") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = atoi(arg2); // Bit position (immediate value)
      instruction = create_instruction(OPCODE_TURN_HEART, operand1, operand2, 0,
                                       metadata);
    } else if (strcmp(mnemonic, "SEEK_WORD") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction =
          create_instruction(OPCODE_SEEK_WORD, operand1, operand2, 0, metadata);
    } else if (strcmp(mnemonic, "LAY_UP") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = strtol(arg2, NULL, 16); // Memory address
      instruction =
          create_instruction(OPCODE_LAY_UP, operand1, operand2, 0, metadata);
    } else if (strcmp(mnemonic, "RECALL") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = strtol(arg2, NULL, 16); // Memory address
      instruction =
          create_instruction(OPCODE_RECALL, operand1, operand2, 0, metadata);
    } else if (strcmp(mnemonic, "CLEAR") == 0 && num_args == 2) {
      operand1 = strtol(arg1, NULL, 16); // Memory address
      instruction = create_instruction(OPCODE_CLEAR, operand1, 0, 0, metadata);
    } else if (strcmp(mnemonic, "SWAP") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction =
          create_instruction(OPCODE_SWAP, operand1, operand2, 0, metadata);
    } else if (strcmp(mnemonic, "STORE_HOUSE") == 0 && num_args == 2) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction =
          create_instruction(OPCODE_STORE_HOUSE, operand1, 0, 0, metadata);
    } else if (strcmp(mnemonic, "DRAW_FROM_WELL") == 0 && num_args == 2) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction =
          create_instruction(OPCODE_DRAW_FROM_WELL, operand1, 0, 0, metadata);
    } else if (strcmp(mnemonic, "PREPARE_PLACE") == 0 && num_args == 2) {
      operand1 = strtol(arg1, NULL, 16); // Memory size to allocate
      instruction =
          create_instruction(OPCODE_PREPARE_PLACE, operand1, 0, 0, metadata);
    } else if (strcmp(mnemonic, "RETURN_TO_DUST") == 0 && num_args == 2) {
      operand1 = strtol(arg1, NULL, 16); // Memory address to free
      instruction =
          create_instruction(OPCODE_RETURN_TO_DUST, operand1, 0, 0, metadata);
    } else if (strcmp(mnemonic, "WEIGH") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction =
          create_instruction(OPCODE_WEIGH, operand1, operand2, 0, metadata);
    } else if (strcmp(mnemonic, "WAIT") == 0 && num_args == 2) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction = create_instruction(OPCODE_WAIT, operand1, 0, 0, metadata);
    } else if (strcmp(mnemonic, "GO") == 0 && num_args == 2) {
      operand1 = strtol(arg1, NULL, 16); // Address
      instruction = create_instruction(OPCODE_GO, operand1, 0, 0, metadata);
    } else if (strcmp(mnemonic, "DIAGNOSE") == 0 && num_args == 1) {
      instruction = create_instruction(OPCODE_DIAGNOSE, 0, 0, 0, metadata);
    } else if (strcmp(mnemonic, "CALL") == 0 && num_args == 2) {
      operand1 = strtol(arg1, NULL, 16); // Subroutine address
      instruction = create_instruction(OPCODE_CALL, operand1, 0, 0, metadata);
    } else if (strcmp(mnemonic, "RETURN") == 0 && num_args == 1) {
      instruction = create_instruction(OPCODE_RETURN, 0, 0, 0, metadata);
    } else if (strcmp(mnemonic, "TRUST") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = strtol(arg2, NULL, 16); // Address
      instruction =
          create_instruction(OPCODE_TRUST, operand1, operand2, 0, metadata);
    } else if (strcmp(mnemonic, "AVOID") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = strtol(arg2, NULL, 16); // Address
      instruction =
          create_instruction(OPCODE_AVOID, operand1, operand2, 0, metadata);
    } else if (strcmp(mnemonic, "WAIT_IN_FAITH") == 0 && num_args == 1) {
      instruction = create_instruction(OPCODE_WAIT_IN_FAITH, 0, 0, 0, metadata);
    } else if (strcmp(mnemonic, "COMPLETE_JOURNEY") == 0 && num_args == 1) {
      instruction =
          create_instruction(OPCODE_COMPLETE_JOURNEY, 0, 0, 0, metadata);
    } else if (strcmp(mnemonic, "LIFT_UP") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction =
          create_instruction(OPCODE_LIFT_UP, operand1, operand2, 0, metadata);
    } else if (strcmp(mnemonic, "BOW_DOWN") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction =
          create_instruction(OPCODE_BOW_DOWN, operand1, operand2, 0, metadata);
    } else if (strcmp(mnemonic, "RISE_TO") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction =
          create_instruction(OPCODE_RISE_TO, operand1, operand2, 0, metadata);
    } else if (strcmp(mnemonic, "FALL_TO") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction =
          create_instruction(OPCODE_FALL_TO, operand1, operand2, 0, metadata);
    } else if (strcmp(mnemonic, "EXAMINE_HEART") == 0 && num_args == 1) {
      instruction = create_instruction(OPCODE_EXAMINE_HEART, 0, 0, 0, metadata);
    } else if (strcmp(mnemonic, "PAUSE_AND_CONSIDER") == 0 && num_args == 1) {
      instruction =
          create_instruction(OPCODE_PAUSE_AND_CONSIDER, 0, 0, 0, metadata);
    } else if (strcmp(mnemonic, "HONOR_BOUNDARY") == 0 && num_args == 3) {
      operand1 = atoi(arg1); // Value to validate
      operand2 = atoi(arg2); // Lower bound
      operand3 = atoi(arg3); // Upper bound
      instruction = create_instruction(OPCODE_HONOR_BOUNDARY, operand1,
                                       operand2, operand3, metadata);
    } else if (strcmp(mnemonic, "SNARE_ESCAPE") == 0 && num_args == 1) {
      instruction = create_instruction(OPCODE_SNARE_ESCAPE, 0, 0, 0, metadata);
    } else if (strcmp(mnemonic, "PAUSE_PATH") == 0 && num_args == 1) {
      instruction = create_instruction(OPCODE_PAUSE_PATH, 0, 0, 0, metadata);
    } else if (strcmp(mnemonic, "SEARCH_DEPTH") == 0 && num_args == 3) {
      operand1 = strtol(arg1, NULL, 16); // Starting address
      operand2 = strtol(arg2, NULL, 16); // Ending address
      instruction = create_instruction(OPCODE_SEARCH_DEPTH, operand1, operand2,
                                       0, metadata);
    } else if (strcmp(mnemonic, "RAISE_UP") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction =
          create_instruction(OPCODE_RAISE_UP, operand1, operand2, 0, metadata);
    } else if (strcmp(mnemonic, "LAY_FLAT") == 0 && num_args == 2) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction =
          create_instruction(OPCODE_LAY_FLAT, operand1, 0, 0, metadata);
    } else if (strcmp(mnemonic, "MEASURE_ANGLE") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = atoi(arg2); // Angle or specific value
      instruction = create_instruction(OPCODE_MEASURE_ANGLE, operand1, operand2,
                                       0, metadata);
    } else if (strcmp(mnemonic, "SEEK_DEPTH") == 0 && num_args == 2) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction =
          create_instruction(OPCODE_SEEK_DEPTH, operand1, 0, 0, metadata);
    } else if (strcmp(mnemonic, "ASCEND_HIGHER") == 0 && num_args == 3) {
      operand1 = (strcmp(arg1, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg1, "B") == 0) ? REGISTER_B
                 : (strcmp(arg1, "C") == 0) ? REGISTER_C
                 : (strcmp(arg1, "D") == 0) ? REGISTER_D
                 : (strcmp(arg1, "E") == 0) ? REGISTER_E
                 : (strcmp(arg1, "F") == 0) ? REGISTER_F
                 : (strcmp(arg1, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction = create_instruction(OPCODE_ASCEND_HIGHER, operand1, operand2,
                                       0, metadata);
    } else if (strcmp(mnemonic, "DRAW_WATER") == 0 && num_args == 2) {
      operand1 = atoi(arg1); // Device ID or input source
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction = create_instruction(OPCODE_DRAW_WATER, operand1, operand2, 0,
                                       metadata);
    } else if (strcmp(mnemonic, "POUR_OUT") == 0 && num_args == 2) {
      operand1 = atoi(arg1); // Device ID or output destination
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction =
          create_instruction(OPCODE_POUR_OUT, operand1, operand2, 0, metadata);
    } else if (strcmp(mnemonic, "DRAW_FROM_STREAM") == 0 && num_args == 2) {
      operand1 = atoi(arg1); // I/O port address
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction = create_instruction(OPCODE_DRAW_FROM_STREAM, operand1,
                                       operand2, 0, metadata);
    } else if (strcmp(mnemonic, "POUR_OUT_VESSEL") == 0 && num_args == 2) {
      operand1 = atoi(arg1); // I/O port address
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction = create_instruction(OPCODE_POUR_OUT_VESSEL, operand1,
                                       operand2, 0, metadata);
    } else if (strcmp(mnemonic, "BIND") == 0 && num_args == 1) {
      operand1 = atoi(arg1); // Lock ID or resource identifier
      instruction = create_instruction(OPCODE_BIND, operand1, 0, 0, metadata);
    } else if (strcmp(mnemonic, "LOOSE") == 0 && num_args == 1) {
      operand1 = atoi(arg1); // Lock ID or resource identifier
      instruction = create_instruction(OPCODE_LOOSE, operand1, 0, 0, metadata);
    } else if (strcmp(mnemonic, "TRUMPET_CALL") == 0 && num_args == 0) {
      instruction = create_instruction(OPCODE_TRUMPET_CALL, 0, 0, 0, metadata);
    } else if (strcmp(mnemonic, "DIVINE_REQUEST") == 0 && num_args == 1) {
      operand1 = atoi(arg1); // System call number
      instruction =
          create_instruction(OPCODE_DIVINE_REQUEST, operand1, 0, 0, metadata);
    } else if (strcmp(mnemonic, "SABBATH_REST") == 0 && num_args == 0) {
      instruction = create_instruction(OPCODE_SABBATH_REST, 0, 0, 0, metadata);
    } else if (strcmp(mnemonic, "SOUND_TRUMPET") == 0 && num_args == 0) {
      instruction = create_instruction(OPCODE_SOUND_TRUMPET, 0, 0, 0, metadata);
    } else if (strcmp(mnemonic, "SILENCE_TRUMPET") == 0 && num_args == 0) {
      instruction =
          create_instruction(OPCODE_SILENCE_TRUMPET, 0, 0, 0, metadata);
    } else if (strcmp(mnemonic, "SEND_MESSAGE") == 0 && num_args == 3) {
      operand1 = atoi(arg1); // Network address
      operand2 = atoi(arg2); // Data to send
      operand3 = atoi(arg3); // Optional flags or context
      instruction = create_instruction(OPCODE_SEND_MESSAGE, operand1, operand2,
                                       operand3, metadata);
    } else if (strcmp(mnemonic, "RECEIVE_MESSAGE") == 0 && num_args == 2) {
      operand1 = atoi(arg1); // Network address
      operand2 = (strcmp(arg2, "A") == 0)   ? REGISTER_A
                 : (strcmp(arg2, "B") == 0) ? REGISTER_B
                 : (strcmp(arg2, "C") == 0) ? REGISTER_C
                 : (strcmp(arg2, "D") == 0) ? REGISTER_D
                 : (strcmp(arg2, "E") == 0) ? REGISTER_E
                 : (strcmp(arg2, "F") == 0) ? REGISTER_F
                 : (strcmp(arg2, "G") == 0) ? REGISTER_G
                                            : REGISTER_H;
      instruction = create_instruction(OPCODE_RECEIVE_MESSAGE, operand1,
                                       operand2, 0, metadata);
    } else if (strcmp(mnemonic, "DIVIDE_LABOR") == 0 && num_args == 2) {
      operand1 = atoi(arg1); // Task identifier
      operand2 = atoi(arg2); // Number of workers
      instruction = create_instruction(OPCODE_DIVIDE_LABOR, operand1, operand2,
                                       0, metadata);
    } else if (strcmp(mnemonic, "GAIN_WISDOM") == 0 && num_args == 2) {
      operand1 = atoi(arg1); // Pattern ID
      operand2 = atoi(arg2); // Metadata or context
      instruction = create_instruction(OPCODE_GAIN_WISDOM, operand1, operand2,
                                       0, metadata);
    } else if (strcmp(mnemonic, "FORSAKE_MEMORY") == 0 && num_args == 1) {
      operand1 = atoi(arg1); // Pattern ID to erase
      instruction =
          create_instruction(OPCODE_FORSAKE_MEMORY, operand1, 0, 0, metadata);
    } else if (strcmp(mnemonic, "RESTORE_STATE") == 0 && num_args == 2) {
      operand1 = atoi(arg1); // State ID or snapshot
      operand2 = atoi(arg2); // Recovery metadata
      instruction = create_instruction(OPCODE_RESTORE_STATE, operand1, operand2,
                                       0, metadata);
    } else if (strcmp(mnemonic, "CENSUS_MARK") == 0 && num_args == 2) {
      operand1 = atoi(arg1); // Data ID
      operand2 = atoi(arg2); // Context or integrity level
      instruction = create_instruction(OPCODE_CENSUS_MARK, operand1, operand2,
                                       0, metadata);
    } else if (strcmp(mnemonic, "PROCLAIM") == 0 && num_args == 2) {
      operand1 = atoi(arg1); // Network range or node group
      operand2 = atoi(arg2); // Message or data ID
      instruction =
          create_instruction(OPCODE_PROCLAIM, operand1, operand2, 0, metadata);
    } else if (strcmp(mnemonic, "SEAL") == 0 && num_args == 3) {
      operand1 = atoi(arg1); // Data ID
      operand2 = atoi(arg2); // Encryption key
      operand3 = atoi(arg3); // Optional flags
      instruction = create_instruction(OPCODE_SEAL, operand1, operand2,
                                       operand3, metadata);
    } else if (strcmp(mnemonic, "UNSEAL") == 0 && num_args == 3) {
      operand1 = atoi(arg1); // Data ID
      operand2 = atoi(arg2); // Decryption key
      operand3 = atoi(arg3); // Optional flags
      instruction = create_instruction(OPCODE_UNSEAL, operand1, operand2,
                                       operand3, metadata);
    } else if (strcmp(mnemonic, "MULTIPLY_HARVEST") == 0 && num_args == 3) {
      operand1 = atoi(arg1); // Matrix 1 ID
      operand2 = atoi(arg2); // Matrix 2 ID
      operand3 = atoi(arg3); // Result matrix ID
      instruction = create_instruction(OPCODE_MULTIPLY_HARVEST, operand1,
                                       operand2, operand3, metadata);
    } else if (strcmp(mnemonic, "INVERT_ORDER") == 0 && num_args == 2) {
      operand1 = atoi(arg1); // Matrix ID
      operand2 = atoi(arg2); // Result matrix ID
      instruction = create_instruction(OPCODE_INVERT_ORDER, operand1, operand2,
                                       0, metadata);
    } else if (strcmp(mnemonic, "COUNT_BLESSINGS") == 0 && num_args == 2) {
      operand1 = atoi(arg1); // Series ID
      operand2 = atoi(arg2); // Sum result location
      instruction = create_instruction(OPCODE_COUNT_BLESSINGS, operand1,
                                       operand2, 0, metadata);
    } else if (strcmp(mnemonic, "UNIFY_THREAD") == 0 && num_args == 3) {
      operand1 = atoi(arg1); // Thread ID
      operand2 = atoi(arg2); // Action: 0 = create, 1 = pause, 2 = terminate
      operand3 = atoi(arg3); // Priority or context
      instruction = create_instruction(OPCODE_UNIFY_THREAD, operand1, operand2,
                                       operand3, metadata);
    } else if (strcmp(mnemonic, "SEASON_SYNC") == 0 && num_args == 1) {
      operand1 = atoi(arg1); // Time synchronization target or context
      instruction =
          create_instruction(OPCODE_SEASON_SYNC, operand1, 0, 0, metadata);
    } else if (strcmp(mnemonic, "DISCERN_PATTERN") == 0 && num_args == 2) {
      operand1 = atoi(arg1); // Input pattern ID
      operand2 = atoi(arg2); // Output pattern ID or interpretation context
      instruction = create_instruction(OPCODE_DISCERN_PATTERN, operand1,
                                       operand2, 0, metadata);
    } // Add additional mnemonic cases for other opcodes here...

    else if (strcmp(mnemonic, "END_RELATION") == 0 && num_args == 1) {
      instruction = create_instruction(OPCODE_END_RELATION, 0, 0, 0, metadata);
    } else {
      int expected_args = expected_argument_count(mnemonic);
      if (expected_args != -1 && expected_args != num_args) {
        fprintf(
            stderr,
            "DEBUG: Argument count mismatch for mnemonic '%s' on line %d.\n",
            mnemonic, line_number);
        fprintf(stderr, "DEBUG: Expected %d arguments, but got %d.\n",
                expected_args, num_args);
      } else {
        fprintf(stderr,
                "DEBUG: Unknown mnemonic encountered: '%s' on line %d\n",
                mnemonic, line_number);
      }

      fprintf(stderr,
              "Error: Unknown instruction or mnemonic '%s' on line %d: %s\n",
              mnemonic, line_number, line);
      fclose(infile);
      fclose(outfile);
      exit(EXIT_FAILURE);
    }

    // Parse metadata if present
    char *metadata_comment = strstr(line, ";");
    if (metadata_comment) {
      metadata = encode_metadata(metadata_comment + 1); // Skip ";"
      instruction.metadata = metadata;
    }

    // Write the instruction to the binary file
    fwrite(&instruction, sizeof(struct OmniCodeInstruction), 1, outfile);

    // Verbose debugging
    if (verbose) {
      printf("Line %d: Assembled instruction:\n", line_number);
      printf("  Opcode: 0x%02X\n", instruction.opcode);
      printf("  Operand1: 0x%08X\n", instruction.operand1);
      printf("  Operand2: 0x%08X\n", instruction.operand2);
      printf("  Operand3: 0x%08X\n", instruction.operand3);
      printf("  Metadata: 0x%016llX\n", instruction.metadata);
    }
  }

  fclose(infile);
  fclose(outfile);
  printf("Assembled successfully to %s\n", output_file);
}

// Main function for the assembler
int main(int argc, char *argv[]) {
  if (argc < 3 || argc > 4) {
    printf("Usage: %s <input_file> <output_file> [--verbose]\n", argv[0]);
    return 1;
  }

  bool verbose = (argc == 4 && strcmp(argv[3], "--verbose") == 0);
  assemble(argv[1], argv[2], verbose);
  return 0;
}

// Function to validate a mnemonic string
int validate_mnemonic(const char *mnemonic) {
  for (int i = 0; mnemonic[i] != '\0'; i++) {
    if (!isalpha(mnemonic[i]) && mnemonic[i] != '_') {
      fprintf(stderr,
              "Error: Invalid mnemonic '%s'. Mnemonics must contain only "
              "letters and underscores.\n",
              mnemonic);
      return 0; // Return 0 if invalid
    }
  }
  return 1; // Return 1 if valid
}

// Function to handle errors with errno
void handle_error(const char *message) {
  char errbuf[256]; // Buffer for thread-safe strerror_r
  strerror_r(errno, errbuf, sizeof(errbuf)); // Get error message safely

  fprintf(stderr, "%s: %s (errno: %d)\n", message, errbuf, errno);
  exit(EXIT_FAILURE);
}

// Function to return the expected argument count for a mnemonic
int expected_argument_count(const char *mnemonic) {
  if (strcmp(mnemonic, "SET") == 0)
    return 3;
  if (strcmp(mnemonic, "GATHER") == 0)
    return 4;
  if (strcmp(mnemonic, "REMOVE") == 0)
    return 4;
  if (strcmp(mnemonic, "FRUIT") == 0)
    return 4;
  if (strcmp(mnemonic, "PORTION") == 0)
    return 4;
  if (strcmp(mnemonic, "INCREMENT") == 0)
    return 2;
  if (strcmp(mnemonic, "DECREMENT") == 0)
    return 2;
  if (strcmp(mnemonic, "BREAD_ADD") == 0)
    return 3;
  if (strcmp(mnemonic, "DEBT_RELEASE") == 0)
    return 3;
  if (strcmp(mnemonic, "SEED_MULTIPLY") == 0)
    return 3;
  if (strcmp(mnemonic, "PORTION_DIVIDE") == 0)
    return 3;
  if (strcmp(mnemonic, "REMAINDER") == 0)
    return 3;
  if (strcmp(mnemonic, "HARVEST_ADD") == 0)
    return 4;
  if (strcmp(mnemonic, "ALIGN") == 0)
    return 3;
  if (strcmp(mnemonic, "OFFER") == 0)
    return 3;
  if (strcmp(mnemonic, "DISCERN") == 0)
    return 2;
  if (strcmp(mnemonic, "LANTERN") == 0)
    return 2;
  if (strcmp(mnemonic, "TAPER") == 0)
    return 2;
  if (strcmp(mnemonic, "CYCLE_LEFT") == 0)
    return 2;
  if (strcmp(mnemonic, "CYCLE_RIGHT") == 0)
    return 2;
  if (strcmp(mnemonic, "WORDS_COMPARE") == 0)
    return 3;
  if (strcmp(mnemonic, "WORDS_MEASURE") == 0)
    return 2;
  if (strcmp(mnemonic, "WORDS_COPY") == 0)
    return 3;
  if (strcmp(mnemonic, "LAY_UP") == 0)
    return 3;
  if (strcmp(mnemonic, "RECALL") == 0)
    return 3;
  if (strcmp(mnemonic, "CLEAR") == 0)
    return 2;
  if (strcmp(mnemonic, "SWAP") == 0)
    return 3;
  if (strcmp(mnemonic, "STORE_HOUSE") == 0)
    return 2;
  if (strcmp(mnemonic, "DRAW_FROM_WELL") == 0)
    return 2;
  if (strcmp(mnemonic, "WAIT") == 0)
    return 2;
  if (strcmp(mnemonic, "GO") == 0)
    return 2;
  if (strcmp(mnemonic, "DIAGNOSE") == 0)
    return 1;
  if (strcmp(mnemonic, "CALL") == 0)
    return 2;
  if (strcmp(mnemonic, "RETURN") == 0)
    return 1;
  if (strcmp(mnemonic, "EXAMINE_HEART") == 0)
    return 1;
  if (strcmp(mnemonic, "PAUSE_AND_CONSIDER") == 0)
    return 1;
  if (strcmp(mnemonic, "RAISE_UP") == 0)
    return 3;
  if (strcmp(mnemonic, "LAY_FLAT") == 0)
    return 2;
  if (strcmp(mnemonic, "MEASURE_ANGLE") == 0)
    return 2;
  if (strcmp(mnemonic, "DRAW_WATER") == 0)
    return 2;
  if (strcmp(mnemonic, "POUR_OUT") == 0)
    return 2;
  if (strcmp(mnemonic, "SEND_MESSAGE") == 0)
    return 3;
  if (strcmp(mnemonic, "RECEIVE_MESSAGE") == 0)
    return 3;
  if (strcmp(mnemonic, "SEAL") == 0)
    return 2;
  if (strcmp(mnemonic, "UNSEAL") == 0)
    return 2;

  return -1; // Return -1 for unknown mnemonics
}