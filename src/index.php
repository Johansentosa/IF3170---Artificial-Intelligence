<!DOCTYPE html>
<html>
<head>
    <title>Jadwal Mata Kuliah Teknink Informatika</title>
    	<link type="text/css" rel="stylesheet" href="media/layout.css" />    

        <link type="text/css" rel="stylesheet" href="themes/calendar_g.css" />    
        <link type="text/css" rel="stylesheet" href="themes/calendar_green.css" />    
        <link type="text/css" rel="stylesheet" href="themes/calendar_traditional.css" />    
        <link type="text/css" rel="stylesheet" href="themes/calendar_transparent.css" />    
        <link type="text/css" rel="stylesheet" href="themes/calendar_white.css" />    

	<!-- helper libraries -->
	<script src="js/jquery-1.9.1.min.js" type="text/javascript"></script>
	
	<!-- daypilot libraries -->
        <script src="js/daypilot/daypilot-all.min1.js" type="text/javascript"></script>
	
</head>
<body>
	        <div id="header">
			<div class="bg-help">
				<div class="inBox">
					<h1 id="logo"><a href='http://code.daypilot.org/17910/html5-event-calendar-open-source'>JADWAL MATA KULIAH TEKNIK INFORMATIKA</a></h1>
					<p id="claim">By : Johan</p>
					<hr class="hidden" />
				</div>
			</div>
        </div>
        <div class="shadow"></div>
        <div class="hideSkipLink">
        </div>
        <div class="main">
            
            <div style="float:left; width: 130px;">
                <div id="nav"></div>
            </div>
            <div style="margin-left: 70px;">
				<div class="space"><b> Jadwal Mata Kuliah Teknik Informatika </div>
                <div id="dp"></div>
            </div>

            <script type="text/javascript">
                
                var dp = new DayPilot.Calendar("dp");
				dp.init();
                dp.viewType = "Resources";
				dp.theme="calendar_traditional";
				dp.columns = [
				  { name: "Monday", id: "1", start: "2013-03-25" },
				  { name: "Tuesday", id: "2", start: "2013-03-25"},
				  { name: "Wednesday", id: "3", start: "2013-03-25" },
				  { name: "Thrusday", id: "4",start: "2013-03-25" },
				  { name: "Friday", id: "5", start: "2013-03-25" }
				];
				
				dp.events.list = [
					<?php
						exec('GA', $out);
						
						$id=1;
						
						if (sizeof($out)==0){
														
						} 
						else{
							for($i=2; $i<sizeof($out);$i++){
								$var = explode(",", $out[$i]);
								if ((int)$var[1]<10){
									$starttime= "0".$var[1];
								}
								$endtime = (int)$starttime+(int)$var[4];
								if ((int)$endtime<10){
									$endtime= "0".$endtime;
								}
								if ($i==2){
									echo '{ start: "2013-03-25T'.$starttime.':00:00",';
									echo 'end: "2013-03-25T'.$endtime.':00:00",';
									echo 'id: "'.$id.'",';
									echo 'text: "'.$var[0].'<br>'.'R'.$var[2].'",';
									echo 'resource: "'.$var[3].'"}';
									$id++;
								}else{
									echo ',{ start: "2013-03-25T'.$starttime.':00:00",';
									echo 'end: "2013-03-25T'.$endtime.':00:00",';
									echo 'id: "'.$id.'",';
									echo 'text: "'.$var[0].'<br>'.'R'.$var[2].'",';
									echo 'resource: "'.$var[3].'"}';
									$id++;
								}
							}
						}
								
					?>
					
				];
				
				/*dp.events.list = [
				{
				  start: "2013-03-25T07:00:00",
				  end: "2013-03-25T14:00:00",
				  id: "1",
				  text: "IF1234 - Penteel Resource <br> R7602",
				  resource: "3"
				},
				{
				  start: "2013-03-25T15:00:00",
				  end: "2013-03-25T17:00:00",
				  id: "2",
				  text: "IF5678 - Kripto <br> R7606",
				  resource: "5"
				}
				];*/
				dp.update();
				
                dp.events.add(e);
								
				dp.onEventMoved = function (args) {
                    $.post("backend_move.php", 
                            {
                                id: args.e.id(),
                                newStart: args.newStart.toString(),
                                newEnd: args.newEnd.toString()
                            }, 
                            function() {
                                console.log("Moved.");
                            });
                };

                dp.onEventResized = function (args) {
                    $.post("backend_resize.php", 
                            {
                                id: args.e.id(),
                                newStart: args.newStart.toString(),
                                newEnd: args.newEnd.toString()
                            }, 
                            function() {
                                console.log("Resized.");
                            });
                };

                // event creating
                /*dp.onTimeRangeSelected = function (args) {
                    var name = prompt("New event name:", "Event");
                    dp.clearSelection();
                    if (!name) return;
                    var e = new DayPilot.Event({
                        start: args.start,
                        end: args.end,
                        id: DayPilot.guid(),
                        resource: args.resource,
                        text: name
                    });
                    dp.events.add(e);

                    $.post("backend_create.php", 
                            {
                                start: args.start.toString(),
                                end: args.end.toString(),
                                name: name
                            }, 
                            function() {
                                console.log("Created.");
                            });
                };*/

                dp.onEventClick = function(args) {
                    alert("clicked: " + args.e.id());
                };

                dp.init();
				
				loadEvents();

                function loadEvents() {
                    var start = dp.visibleStart();
                    var end = dp.visibleEnd();

                    $.post("backend_events.php", 
                    {
                        start: start.toString(),
                        end: end.toString()
                    }, 
                    function(data) {
                        //console.log(data);
                        dp.events.list = data;
                        dp.update();
                    });
                } 

            </script>
            
            <script type="text/javascript">
            $(document).ready(function() {
                $("#theme").change(function(e) {
                    dp.theme = this.value;
                    dp.update();
                });
            });  
            </script>

        </div>
        <div class="clear">
        </div>
        
</body>
</html>

