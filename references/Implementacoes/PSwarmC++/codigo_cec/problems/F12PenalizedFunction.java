/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package clonalg_metamodel.problems;

import clonalg_metamodel.base.Problem;
import clonalg_metamodel.util.Configuration;

/**
 *
 * @author hedersb
 */
public class F12PenalizedFunction extends Problem {

    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;
    private double[] boundBase = {-50, 50};

    public F12PenalizedFunction(Configuration configuration, int dimension) {
        this.configuration = configuration;
        this.dimension = dimension;
    }

    @Override
    protected double[] evaluateSolution(Object gene) {
        double[] x = null;
        if (gene instanceof double[]) {
            x = (double[]) gene;
        } else {
            int[] variableSize = new int[getNumberOfVariables()];
            for (int i = 0; i < variableSize.length; i++) {
                variableSize[i] = configuration.getBinaryEncodingContinuousVariable();
            }
            x = configuration.getUtilitaries().getRealFromBinary((boolean[])gene, variableSize, getBounds(), true, configuration.getBinaryEncodingContinuousVariable(), this);
        }
        double[] result = new double[1];
        double sum1 = 0;
	double sum2 = 0;
	double aux;
	double[] y = getY(x, dimension);
        for (int i = 0; i < dimension-1; i++) {
	    aux = (y[i]-1);
            sum1 += aux*aux*(1 + 10*Math.pow(Math.sin(Math.PI*y[i+1]), 2));
        }
	for (int i = 0; i < dimension; i++) {
            sum2 += u(x[i], 10, 100, 4);
        }
	aux = y[dimension-1] - 1;
        result[0] = (Math.PI/30d)*(10*Math.pow(Math.sin(Math.PI*y[0]), 2) + sum1 + aux*aux) + sum2;
        return result;
    }

    @Override
    public double[][] getBounds() {
        if (bound==null) {
            bound = new double[dimension][2];
            for (int i = 0; i < bound.length; i++) {
                bound[i][0] = boundBase[0];
                bound[i][1] = boundBase[1];
            }
        }
        return bound;
    }

    @Override
    public int getMaxNumberFitnessFuntionEvaluation() {
        //return 150000;
	return 15000;
    }

    private double u(double x, double a, double k, double m) {
	return x > a? k*Math.pow(x-a, m): x < -a? k*Math.pow(-x-a, m): 0;
    }

    private double[] getY(double[] x, int dimension) {
	double[] y = new double[dimension];

	for (int i = 0; i < dimension; i++) {
	    y[i] = 1 + 0.25*(x[i] + 1);
	}

	return y;
    }

    @Override
    public double getBestValue() {
	//return 9.2*Math.pow(10, -6); //FEP
	//return 0.632;
	return 0.7701294; //icaris2010
    }

    @Override
    public Problem clone() {
	return new F12PenalizedFunction(configuration, dimension);
    }
}
