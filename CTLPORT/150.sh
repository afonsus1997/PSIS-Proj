./ctldoor A&
ID = pidof ctldoor


echo -n "1234" > /proc/$ID/fd/0

