cd ..
soma=0
for i in $(seq 1 30)
do
	res=`./paralelo entradas/500m_30.txt roots -t`
	soma=`python -c "print $res+$soma"`
done
python -c "print '500m-30 - 1 thread', $soma/30.0"
