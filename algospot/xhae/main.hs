import Control.Monad
import Data.List
import Data.Maybe

num = [0..10]
str = ["zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"]

ston s = num !! (fromJust (elemIndex s str))
ntos n = str !! (fromJust (elemIndex n num))

getInt = read `fmap` getLine :: IO Int

main = do
	numCases <- getInt
	replicateM_ numCases solve

solve = do
	[a, op, b, eq_symbol, c] <- words `fmap` getLine
	case op of
		"+" -> comp (ston a + ston b) c
		"-" -> comp (ston a - ston b) c
		"*" -> comp (ston a * ston b) c

comp soln c = do
	if soln < 0 || soln > 10
	then putStrLn "No"
	else
		if sort (ntos soln) == sort c
		then putStrLn "Yes"
		else putStrLn "No"
