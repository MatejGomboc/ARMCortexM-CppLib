# Python peripheral for test output
# This file can be used as an alternative to inline script

def init():
    self.output_buffer = ""
    self.char_callback = None

def handle_write(offset, value):
    if offset == 0:  # Write to output register
        char = chr(value & 0xFF)
        self.output_buffer += char
        
        # Log the character
        self.machine.GetLogger().Log(LogLevel.Info, char, append=True)
        
        # Also print for immediate visibility
        if char == '\n':
            print(self.output_buffer.rstrip())
            self.output_buffer = ""
        
        # If callback is set, call it
        if self.char_callback:
            self.char_callback(char)
    
    return True

def handle_read(offset):
    # Reading always returns 0 (not implemented)
    return 0

# Register handlers
self.OnWrite = handle_write
self.OnRead = handle_read
