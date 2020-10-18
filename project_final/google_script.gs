function doPost(e) { 
  Logger.log( JSON.stringify(e) );  // view parameters
  var result = 'Ok\n'; // assume success
  if (e.parameter == 'undefined') {
    result = 'No Parameters';
  } else {
    var sheet_id = '1qOQLTV4blW8YfqnutcYfN3RP9ngthLUmmGXbg4OjNns';      // Spreadsheet ID
    var sheet = SpreadsheetApp.openById(sheet_id).getActiveSheet();     // get Active sheet
    var newRow = sheet.getLastRow() + 1;                        
    var rowData = ['','','','','',''];
    var Range = sheet.getDataRange();
    
    d = new Date();
    
    rowData[0] = d; // Timestamp in column A
    rowData[1] = d.toLocaleTimeString(); // Timestamp in column A
    
    for (var param in e.parameter) {
      Logger.log('In for loop, param=' + param);
      var value = stripQuotes(e.parameter[param]);
      Logger.log(param + ':' + e.parameter[param]);
      switch (param) {
        case 'status=add&topic':
          rowData[3] = value; 
          rowData[2] = 'add';
          result += 'Written on column topic\n';
          break;
        case 'status=del&topic':
          rowData[3] = value;
          rowData[2] = 'del';
          result += 'Written on column topic\n';
          break;
        case 'detail': 
          rowData[4] = value; 
          result += 'Written on column details\n';
          break;
        default:
          result = "unsupported parameter\n";
      }
    }
    Logger.log(JSON.stringify(rowData));
    
    // Update new row below
    var newRange = sheet.getRange(newRow, 1, 1, rowData.length - 2);
    
    if (rowData[2] === 'add') {
      var realData = [rowData[0], rowData[1], rowData[3], rowData[4]]
      newRange.setValues([realData]);
    
    } else if (rowData[2] === 'del') {
      var success_del = 0
      var rangeVals = Range.getValues();
      
      for (var i = rangeVals.length-1; i > 0; i--) {
        if (String(rangeVals[i][2]).toLowerCase().startsWith(rowData[3].toLowerCase())) {
          sheet.deleteRow(i + 1);
          success_del = 1
        }
      }
      if (success_del) result = `Delete Topic: \"${rowData[3]}\" already. >w<`;
      else result= `Not found Topic:\"${rowData[3]}\" in Database. T^T`;
    } else {
      Logger.log("JS is fuck");
    }
    
  }
  var style = '<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">';
  style += '<style>.success {background-color: #ddffdd;border-left: 6px solid #4CAF50;}</style>';
  
  var heading = "<h1>Report Operation</h1>"
  heading += '<div class="success"><p><strong>Success!</strong> Congratulations and BRAVO!</p></div>'
  
  var content = HtmlService.createTemplate('<p>Connect to Database add note Topic: "<?= topic ?>", Detail: "<?= detail ?>"</p>');
  
  content.topic = rowData[3];
  content.detail = rowData[4];
  
  var list_log = '<ul>'
  result.split("\n").forEach(function(line, idx, arr){
    if (line.length >= 3) list_log = list_log + `<li> ${line} </li>`;
  });
  list_log = list_log + "</ul>"
  list_log = list_log + '<button class="btn btn-primary" onclick="goBack()">Go Back</button>';
  list_log = list_log + '<script>function goBack() {window.history.back();}</script>';
  
  
  var HTMLOutput = HtmlService.createHtmlOutput();
  HTMLOutput.append(style);
  HTMLOutput.append(heading);
  HTMLOutput.append(content = content.evaluate().getContent() );
  HTMLOutput.append(list_log);

  return HTMLOutput
}

function stripQuotes( value ) {
  return value.replace(/^["']|['"]$/g, "");
}
