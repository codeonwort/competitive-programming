import Data.List

main = do
	s <- getLine
	let (a,deb) = break (== '.') s
	let (d,e:b) = break (== 'e') (tail deb)
	let d' = d ++ repeat '0'
	let b' = read b :: Int
	let a' = a ++ take b' d'
	let a'' = dropWhile (== '0') a'
	let a''' = if a'' == [] then "0" else a''
	let d'' = take (length d) (drop b' d')
	let d''' = reverse $ dropWhile (== '0') (reverse d'')
	if d''' == []
	then putStrLn a'''
	else putStrLn $ a''' ++ "." ++ d'''
