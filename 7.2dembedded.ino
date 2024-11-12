import speech_recognition as sr  # Importing the speech recognition library
from gpiozero import LED  # Importing LED class from gpiozero library
from time import sleep  # Importing the sleep function from time module

# Creating an LED object connected to GPIO pin 17
led_indicator = LED(17)
# Creating a recognizer object for speech recognition
voice_recognizer = sr.Recognizer()

# Function to listen for commands from an audio file
def listen_for_commands():
    while True:  # Loop indefinitely
        audio_file_path = "/home/kaushik/Music/record.wav"  # Path to the audio file
        if os.path.exists(audio_file_path):  # Check if the file exists
            with sr.AudioFile(audio_file_path) as source:  # Open the audio file
                audio_data = voice_recognizer.record(source)  # Record the audio

                try:
                    # Recognize the speech in the audio data
                    command = voice_recognizer.recognize_sphinx(audio_data)
                    # Print the recognized command
                    print(f"Command understood: {command}")
                    # Return the recognized command
                    return command

                except sr.UnknownValueError:
                    # Print an error message if speech is not recognized
                    print("Apologies, unable to comprehend the command.")
                    return ""

                except sr.RequestError as e:
                    # Print an error message if there's an issue with the recognition service
                    print(f"Error in recognition: {e}")
                    return ""
        else:
            # Print a message if the audio file is not found
            print("Audio file not found.")
            return ""

# Function to control the LED based on the received command
def control_led(command):
    if "on" in command:  # If the command contains "on"
        led_indicator.on()  # Turn on the LED
        # Print a message indicating the LED is illuminated
        print("LED is now illuminated.")
    elif "off" in command:  # If the command contains "off"
        led_indicator.off()  # Turn off the LED
        # Print a message indicating the LED is turned off
        print("LED has been turned off.")

try:
    while True:  # Loop indefinitely
        command = listen_for_commands()  # Listen for commands
        control_led(command)  # Control the LED based on the command
        sleep(0.5)  # Sleep for 0.5 seconds for faster responsiveness
except KeyboardInterrupt:
    # Print a message if the program is terminated manually
    print("Program terminated manually.")
    led_indicator.off()  # Turn off the LED