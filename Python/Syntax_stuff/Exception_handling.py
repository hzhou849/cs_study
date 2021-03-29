   
To catch all exceptions. Pretty handy for debugging.

 import sys
    try:
      untrusted.execute()
    except: # catch *all* exceptions
      e = sys.exc_info()[0]
      write_to_page( "<p>Error: %s</p>" % e )


# To handle exception types
except Exceptions as error_msg:
	print(error_msg)
