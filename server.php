<?php


/*
 * Interpreter
 * based on forth language
 */


$_d=array();/* Data stack */
$_s='';     /* Input string */
$_i=0;      /* Current index in input string */
$_w='';     /* Current word is stored here */
$_q='';     /* Quote status of current word */


/**
 * @brief Checks if character is white space
 */
function iswhite($c)
{
   return
      $c=="\n" ||
      $c=="\r" ||
      $c=="\t" ||
      $c==" ";
}

/**
 * @brief Reads word (or quoted string) from input; can do escapes also
 */
function readw()
{
   global $_s,$_i,$_w,$_q;
   $_q='';
   $_w='';
   $wlen=0;
   $len=strlen($_s);
   $e=0;

   /* Skip whites */
   while ($_i<$len && iswhite($_s[$_i])) $_i++;

   /* Read single word/q-string */
   while ($_i<$len) {
      $c=$_s[$_i];
      if (!$_q && iswhite($c)) break;

      /* Check for escape character */
      if (!$e && $c=='\\') {
         $e=1;
         $_i++;
         continue;
      }

      /* We are not escaping - check for quote */
      if (!$e) {
         if ($c=='"' || $c=='\'') {

            /* End of quoted string */
            if ($_q==$c) break;

            /* Beginning of quoted string */
            if (empty($_w)) {
               $_q=$c;
               $_i++;
               continue;
            }

         }
      } else {
         /* Special escapes */
         if ($c=='n') $c="\n";
         if ($c=='r') $c="\r";
         if ($c=='t') $c="\t";
         $e=0;
      }

      $_w.=$c;
      $wlen++;
      $_i++;
   }

   if ($_q) {
      /* Empty quoted word will return 1 */
      $wlen++;
      /* Skip closing quote */
      $_i++;
   }
   return $wlen;
}


/*
 * Utility functions
 */

/**
 * @brief Generate random key
 * @param $len Length of key to be generated
 * @return key
 */
function genKey($len){
	$n=0;$s='';
	while ($len>0) {
		if (!$n) $n=mt_rand();
		$s.='-qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890_'[$n%64];
		$n=$n>>6;
		$len--;
	}
	return $s;
}

/**
 * @brief Generate key and file for it
 * @return key
 */
function genKeyFile(){
	do {
		$key=genKey(32);
		$path='./keys/'.$key;
	} while (file_exists($path));
	file_put_contents($path,json_encode(array('t'=>time())),LOCK_EX);
	return $key;
}

/**
 * @brief Outputs error message
 * @param $s Message text
 * @return 0 for convenience
 */
function E($s)
{
   echo "\n#E : ".$s."\n";
   return 0;
}


/*
 * Server words
 */

// ( n n - n )
function fc_add()
{
   global $_d;
   if (count($_d)<2) return 0;
   $b=array_pop($_d);
   $a=array_pop($_d);
   $_d[]=$a+$b;
   return 1;
}

// ( n - )
function fc_prt()
{
   global $_d;
   if (count($_d)<1) return 0;
   $a=array_pop($_d);
   echo $a;
   return 1;
}
// ( - )
function fc_motd()
{
   echo 'hello, world';
   return 1;
}
// ( - s )
function fc_autoreg()
{
   global $_d;
   $_d[]=genKeyFile();
   return 1;
}


/*
 * Init
 */

if (!file_exists('./keys')) @mkdir('./keys',0655);


/*
 * Main forth loop
 */

if (!empty($_GET['d'])) {

   /* Decode incomming data */
   $_s=base64_decode(str_replace(array('+','/'),array('-','_'),$_GET['d']));

   /* Loop untile there in input */
   while (readw()) {

      /* Quoted string - add on stack */
      if ($_q)
         $_d[]=$_w;

      /* Number - add on stack */
      else if (is_numeric($_w))
         $_d[]=intval($_w);

      /* Must be NATive function - call it */
      else {
         $fc='fc_'.$_w;
         if (function_exists($fc)) {
            $ret=$fc();
            /* Returned error code */
            if ($ret==0) {
               E("NAT exc : ".$fc);
            }
         } else {
            E("NAT not found : ".$fc);
         }
      }

   }

}
