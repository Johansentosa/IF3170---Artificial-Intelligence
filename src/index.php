<!DOCTYPE html>
<html>
<head>
    <title>Scheduling</title>
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
	
	<!-- style css-->
	<style>
	.button-border-radius-blue {
		padding: 0.5% 4%;
		font-size: 20px;
		color: #fff;
		font-family: 'Lato', sans-serif;
		background-color: #02838b;
		border-radius: 40px;
		border: 3px solid #02838b;
	}
	.button-border-radius-blue:hover {
		color: #fff;
		background-color: #98004a;
		border-radius: 40px;
		border: 1px solid #98004a;
		-webkit-border-radius: 40px;
		-moz-border-radius: 40px;
		-ms-border-radius: 40px;
		-o-border-radius: 40px;
	}

	.container ul {
		list-style: none;
		height: 100%;
		width: 100%;
		margin: 0;
		padding: 0;
	}
	
	ul li{
		color: #AAAAAA;
		display: block;
		position: relative;
		width: 80%;
		height: 80px;
		border-bottom: 1px solid #111111;
		margin: 0;
		padding: 0;
	}
	ul li input[type=radio]{
		position: absolute;
		visibility: hidden;
	}
	ul li label{
		display: block;
		font-size: 20px;
		position: relative;
		font-weight: 300;
		left: 10%;
		top: 36%;
		margin: 10px auto;
		height: 30px;
		z-index: 9;
		cursor: pointer;
		-webkit-transition: all 0.25s linear;
	}
	ul li :hover label{
		color: black;
	}
	ul li .check{
	  display: block;
	  position: absolute;
	  border: 5px solid #AAAAAA;
	  border-radius: 100%;
	  height: 25px;
	  width: 25px;
	  top: 30px;
	  left: 0px;
	  z-index: 5;
	  transition: border .25s linear;
	  -webkit-transition: border .25s linear;
	}
	ul li:hover .check {
	  border: 5px solid black;
	}
	ul li .check::before {
	  display: block;
	  position: absolute;
	  content: '';
	  border-radius: 100%;
	  height: 15px;
	  width: 15px;
	  top: 5px;
	  left: 5px;
	  margin: auto;
		transition: background 0.25s linear;
		-webkit-transition: background 0.25s linear;
	}
	input[type=radio]:checked ~ .check {
	  border: 5px solid #0DFF92;
	}

	input[type=radio]:checked ~ .check::before{
	  background: #0DFF92;
	}
	input[type=radio]:checked ~ lulel{
	  color: #0DFF92;
	}
	
	</style>
	
</head>
<body>
	        <div id="header">
			<div class="bg-help">
				<div class="inBox">
					<h1 id="logo"><a href='http://code.daypilot.org/17910/html5-event-calendar-open-source'>PENDINATOR - Scheduling</a></h1>
					<p id="claim">By : Johan, Kevin Supendi, Christian Anthony, Yeksa Diningrat</p>
					<hr >
				</div>
			</div>
        </div>
        <div class="shadow"></div>
        <div class="hideSkipLink">
        </div>
        <div class="main">
            
            <div style="float:left; width: 130px;">
            
            </div>
            <div style="margin-left: 70px;">
				<div class="space"><b> Jadwal Mata Kuliah Teknik Informatika </div>
                <div id="dp"></div>
				<form name="Algorithm" id="algo" method="get">
					<ul>
						<li>
							<input id="radio-1"  name="radio-group" type="radio" value="GA" checked>
							<label for="radio-1" >Genetic Algorithm</label>
							<div class="check"></div>
						</li>
						<li>
							<input id="radio-2" name="radio-group" type="radio" value="SA" >
							<label for="radio-2" >Simulated Anealing</label>
							<div class="check"><div class="inside"></div></div>
						</li>
						<li>
							<input id="radio-3" name="radio-group" type="radio" value="HC" >
							<label for="radio-3" >Hill Climbing</label>
							<div class="check"><div class="inside"></div></div>
						</li>
					</ul> 
					<input id ="fname" name="fname" type="text" placeholder="Insert filename or path">
					<div id="success"></div>
					<div class="row">
						<div class="form-group col-xs-12">
							<button type="post" class="btn btn-success btn-lg">Send</button>
							<button type="reset" class="btn btn-success btn-lg">Cancel</button>
						</div>

					</div>
				</form><br><br>
            </div>
			<div>
				
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
				
				<?php
					if ($_SERVER["REQUEST_METHOD"] == "GET"){
						$algo= $_GET["radio-group"];
						$fname = $_GET["fname"];
						if ($algo=="GA"){
							exec('../bin/main GA '.$fname, $out, $exitcode);								
						}
						else if($algo=="SA"){
							exec('../bin/main SA '.$fname, $out, $exitcode);
						}
						else if($algo=="HC"){
							exec('../bin/main HC '.$fname, $out, $exitcode);
						}
					}
					if($exitcode!=0){
						echo 'alert("Error!! Error: '.$exitcode.'")';
					}
				?>
					
				
				dp.events.list = [
					<?php					
		
						$id=1;
						
						if (sizeof($out)==0){
														
						} 
						else{
							$color = 0;
							for($i=3; $i<sizeof($out);$i++){
								$plus = 360/sizeof($out);
								$var = explode(",", $out[$i]);
								if ((int)$var[1]<10){
									$starttime= "0".$var[1];
								} else {
									$starttime = $var[1];
								}
								$endtime = (int)$starttime+(int)$var[4];
								if ((int)$endtime<10){
									$endtime= "0".$endtime;
								}
								
								if ($i==3){
									echo '{ start: "2013-03-25T'.$starttime.':00:00",';
									echo 'end: "2013-03-25T'.$endtime.':00:00",';
									echo 'id: "'.$id.'",';
									echo 'text: "'.$var[0].'<br>'.'R'.$var[2].'",';
									echo 'resource: "'.$var[3].'",';
									echo 'backColor : "hsl('.$color.',100%,50%)"}';
									$id++;
									$color = $color+$plus;
								}else{
									echo ',{ start: "2013-03-25T'.$starttime.':00:00",';
									echo 'end: "2013-03-25T'.$endtime.':00:00",';
									echo 'id: "'.$id.'",';
									echo 'text: "'.$var[0].'<br>'.'R'.$var[2].'",';
									echo 'resource: "'.$var[3].'",';
									echo 'backColor : "hsl('.$color.',100%,50%)"}';
									$id++;
									$color = $color+$plus;
								}
							}
						}
								
					?>
					
				];			
				
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
			<div style="margin-left: 70px"><h2><?php
				$var = explode(",", $out[0]);
				$eff = explode(",", $out[1]);
				echo "Jumlah Konflik = ".$var[1]."<br>";
				echo "Keefektivan = ".$eff[1]."%<br>";
			?></h2>
			</div>
			
        </div>
        <div class="clear">
        </div>
        
</body>
</html>

